#pragma once

// C++ standard
#include <cstdint>
#include <memory>
#include <vector>

// Namespace sr --> "software rasterizer"
namespace sr
{
	class Model;

	class Rasterizer
	{
	public:
		Rasterizer();
		~Rasterizer() = default;

		void Initialize(std::uint32_t window_width, std::uint32_t window_height);

		void AddModel(const std::shared_ptr<Model>& model) noexcept;

	private:
		std::vector<std::weak_ptr<Model>> m_models;

		std::uint32_t m_window_width;
		std::uint32_t m_window_height;
	};
}