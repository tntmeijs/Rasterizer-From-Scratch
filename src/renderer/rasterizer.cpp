#include "renderer/rasterizer.hpp"

// Application
#include "renderer/model.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"

sr::Rasterizer::Rasterizer()
	: m_window_width(0)
	, m_window_height(0)
	, m_pixel_data(nullptr)
	, m_clear_color{ 0, 0, 0, 1 }
{
}

sr::Rasterizer::~Rasterizer()
{
	if (m_pixel_data)
		delete[] m_pixel_data;
}

void sr::Rasterizer::Initialize(std::uint32_t window_width, std::uint32_t window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;

	// Allocate memory to store the pixel data in
	m_pixel_data = new std::uint8_t[window_width * window_height * static_cast<std::uint8_t>(settings::BYTES_PER_PIXEL)];
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

const std::uint8_t* const sr::Rasterizer::Render() noexcept
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

	return m_pixel_data;
}

void sr::Rasterizer::ClearScreen()
{
	auto bytes_per_pixel = static_cast<size_t>(settings::BYTES_PER_PIXEL);

	for (size_t i = 0; i < m_window_width * m_window_height * bytes_per_pixel; i += bytes_per_pixel)
	{
		// For each component per pixel, set its color value
		for (size_t j = 0; j < bytes_per_pixel; ++j)
		{
			m_pixel_data[i + j] = m_clear_color[j];
		}
	}
}

void sr::Rasterizer::RasterizeModelWithIndices(const std::shared_ptr<Model>& model)
{
	const auto& vertex_data = model->GetVertexData();
	size_t number_of_triangles = model->GetVertexDataSize() / sizeof(sr::Vertex);

	if (auto ptr = vertex_data.lock())
	{
		// Since there are no indices, assume every three vertices make up a triangle
		for (size_t i = 0; i < number_of_triangles; i += 3)
		{
			RasterizeTriangle(ptr.get()[i].position, ptr.get()[i + 1].position, ptr.get()[i + 2].position);
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
	(void)vertex_0;
	(void)vertex_1;
	(void)vertex_2;
	// #TODO: implement
}
