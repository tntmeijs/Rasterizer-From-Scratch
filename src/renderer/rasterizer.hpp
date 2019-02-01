#pragma once

// C++ standard
#include <memory>
#include <vector>

// Namespace sr --> "software rasterizer"
namespace sr
{
	class Model;

	class Rasterizer
	{
	public:
		Rasterizer() = default;
		~Rasterizer() = default;

		void AddModel(const std::shared_ptr<Model>& model) noexcept;

	private:
		std::vector<std::weak_ptr<Model>> m_models;
	};
}