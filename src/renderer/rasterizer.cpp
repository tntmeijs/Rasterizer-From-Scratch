#include "renderer/rasterizer.hpp"

sr::Rasterizer::Rasterizer()
	: m_window_width(0)
	, m_window_height(0)
{
}

void sr::Rasterizer::Initialize(std::uint32_t window_width, std::uint32_t window_height)
{
	m_window_width = window_width;
	m_window_height = window_height;
}

void sr::Rasterizer::AddModel(const std::shared_ptr<Model>& model) noexcept
{
	m_models.push_back(model);
}
