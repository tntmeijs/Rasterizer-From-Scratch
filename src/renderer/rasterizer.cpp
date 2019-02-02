#include "renderer/rasterizer.hpp"

// Application
#include "renderer/camera.hpp"
#include "renderer/model.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"

sr::Rasterizer::Rasterizer()
	: m_window_width(0)
	, m_window_height(0)
	, m_frame_buffer(nullptr)
	, m_clear_color{ 0, 0, 0, 255 }
	, m_active_camera_index(-1)
{
}

sr::Rasterizer::~Rasterizer()
{
	if (m_frame_buffer)
		delete[] m_frame_buffer;
}

void sr::Rasterizer::Initialize(std::uint32_t window_width, std::uint32_t window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;

	// Allocate memory to store the pixel data in
	m_frame_buffer = new Pixel[window_width * window_height];
}

void sr::Rasterizer::AddModel(const std::shared_ptr<Model>& model, const std::vector<glm::mat4>& model_matrices) noexcept
{
	m_models.emplace_back(model, model_matrices);
}

const int sr::Rasterizer::AddCamera(double field_of_view_degrees, double aspect_ratio, const glm::vec3 & position, const glm::vec3 & target) noexcept
{
	const auto& camera = std::make_shared<Camera>();
	camera->Create(field_of_view_degrees, aspect_ratio, position, target);

	m_cameras.push_back(camera);
	return m_cameras.size() - 1;
}

void sr::Rasterizer::RemoveCamera(int index) noexcept
{
	// Index out of bounds
	if (index < 0 || static_cast<int>(m_cameras.size()) >= index)
		return;

	// Remove the camera at the specified index
	m_cameras.erase(m_cameras.begin() + index);
}

void sr::Rasterizer::SetClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept
{
	m_clear_color[0] = r;
	m_clear_color[1] = g;
	m_clear_color[2] = b;
	m_clear_color[3] = a;
}

void sr::Rasterizer::SetActiveCameraIndex(unsigned int index) noexcept
{
	// Index out of bounds
	if (index < 0 || m_cameras.size() >= index)
		return;

	m_active_camera_index = index;
}

const int sr::Rasterizer::GetActiveCameraIndex() const noexcept
{
	return m_active_camera_index;
}

const sr::Pixel* const sr::Rasterizer::Render() noexcept
{
	// No need to render the scene without a camera
	if (0 > m_active_camera_index || m_cameras.empty())
		return nullptr;

	for (const auto& model : m_models)
	{
		if (const auto& ptr = model.first.lock())
		{
			// Clear the buffer with the specified clear color
			ClearScreen();

			// "Instance models" by rendering the same model multiple times using different matrices
			for (const auto& matrix : model.second)
			{
				// If no index data is available, rasterize the model without indices
				if (ptr->GetIndexDataSize() != 0)
					RasterizeModelWithIndices(ptr, matrix);
				else
					RasterizeModelWithoutIndices(ptr, matrix);
			}
		}
	}

	return m_frame_buffer;
}

void sr::Rasterizer::ClearScreen()
{
	for (size_t i = 0; i < m_window_width * m_window_height; ++i)
	{
		// For each component per pixel, set its color value
		m_frame_buffer[i] =
		{
			m_clear_color[0],
			m_clear_color[1],
			m_clear_color[2],
			m_clear_color[3]
		};
	}
}

void sr::Rasterizer::RasterizeModelWithIndices(const std::shared_ptr<Model>& model, const glm::mat4& matrix)
{
	const auto& vertex_data = model->GetVertexData();
	const auto& index_data = model->GetIndexData();

	size_t number_of_triangles = model->GetIndexDataSize() / 3;

	(void)matrix;
	(void)number_of_triangles;

	// Get a hold of the vertex and index data pointers
	const auto& vertex_data_ptr = vertex_data.lock();
	const auto& index_data_ptr = index_data.lock();

	// If the data is valid, proceed
	if (vertex_data_ptr && index_data_ptr)
	{
	}
}

void sr::Rasterizer::RasterizeModelWithoutIndices(const std::shared_ptr<Model>& model, const glm::mat4& matrix)
{
	(void)model;
	(void)matrix;
	// #TODO: implement
}

void sr::Rasterizer::RasterizeTriangle(const glm::vec3& vertex_0, const glm::vec3& vertex_1, const glm::vec3& vertex_2)
{
	// Base vertex matrix
	glm::mat3 vertex_matrix =
	{
		{ vertex_0.x, vertex_1.x, vertex_2.x },
		{ vertex_0.y, vertex_1.y, vertex_2.y },
		{ vertex_0.z, vertex_1.z, vertex_2.z }
	};

	// Invert the matrix to be able to use it as edge equations
	vertex_matrix = glm::inverse(vertex_matrix);

	// Using the inversed vertex matrix, calculate the edge functions
	glm::vec3 edge_0 = vertex_matrix * glm::vec3(1, 0, 0);
	glm::vec3 edge_1 = vertex_matrix * glm::vec3(0, 1, 0);
	glm::vec3 edge_2 = vertex_matrix * glm::vec3(0, 0, 1);

	// Check each pixel for overlaps
	for (std::uint32_t y = 0; y < m_window_height; ++y)
	{
		for (std::uint32_t x = 0; x < m_window_width; ++x)
		{
			// Sample at the center of the pixel
			glm::vec3 sample = { x + 0.5, y + 0.5, 1.0 };

			// Check the edge functions against each fragment
			float edge_alpha	= glm::dot(edge_0, sample);
			float edge_beta		= glm::dot(edge_1, sample);
			float edge_gamma	= glm::dot(edge_2, sample);

			// If the sample lies on the triangle, it should be shaded
			if ((edge_alpha	>= 0.0)	&&
				(edge_beta	>= 0.0)	&&
				(edge_gamma	>= 0.0))
			{
				auto r = static_cast<std::uint8_t>(glm::floor(255.0 * edge_alpha));
				auto g = static_cast<std::uint8_t>(glm::floor(255.0 * edge_beta));
				auto b = static_cast<std::uint8_t>(glm::floor(255.0 * edge_gamma));

				m_frame_buffer[x + (y * m_window_width)] = { r, g, b, 255 };
			}
		}
	}
}
