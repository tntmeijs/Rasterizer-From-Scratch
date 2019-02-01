#include "renderer/rasterizer.hpp"

void sr::Rasterizer::AddModel(const std::shared_ptr<Model>& model) noexcept
{
	m_models.push_back(model);
}
