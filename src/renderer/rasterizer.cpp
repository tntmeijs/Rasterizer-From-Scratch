#include "renderer/rasterizer.hpp"

// Application
#include "renderer/model.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"

sr::Rasterizer::Rasterizer()
	: m_window_width(0)
	, m_window_height(0)
	, m_frame_buffer(nullptr)
	, m_clear_color{ 0, 0, 0, 255 }
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

void sr::Rasterizer::AddModel(const std::shared_ptr<Model>& model) noexcept
{
	m_models.push_back(model);
}

void sr::Rasterizer::SetClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	m_clear_color[0] = r;
	m_clear_color[1] = g;
	m_clear_color[2] = b;
	m_clear_color[3] = a;
}

const sr::Pixel* const sr::Rasterizer::Render() noexcept
{
	for (const auto& model : m_models)
	{
		if (const auto& ptr = model.lock())
		{
			// Clear the buffer with the specified clear color
			ClearScreen();

			// If no index data is available, rasterize the model without indices
			if (0 == ptr->GetIndexDataSize())
				RasterizeModelWithIndices(ptr);
			else
				RasterizeModelWithoutIndices(ptr);
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

void sr::Rasterizer::RasterizeModelWithIndices(const std::shared_ptr<Model>& model)
{
	const auto& vertex_data = model->GetVertexData();
	size_t number_of_triangles = (model->GetVertexDataSize() / sizeof(sr::Vertex)) / 3;

	if (auto ptr = vertex_data.lock())
	{
		// Since there are no indices, assume every three vertices make up a triangle
		for (size_t i = 0; i < number_of_triangles; i += 3)
		{
			RasterizeTriangle(ptr.get()[i + 0].position, ptr.get()[i + 1].position, ptr.get()[i + 2].position);
		}
	}
}

void sr::Rasterizer::RasterizeModelWithoutIndices(const std::shared_ptr<Model>& model)
{
	(void)model;
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
