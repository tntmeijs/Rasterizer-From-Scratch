#pragma once

// GLM
#include <glm/glm.hpp>

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
		~Rasterizer();

		void Initialize(std::uint32_t window_width, std::uint32_t window_height);
		void AddModel(const std::shared_ptr<Model>& model) noexcept;
		void SetClearColor(const glm::vec4& clear_color);
		void Render() noexcept;

	private:
		void RasterizeModelWithIndices(const std::shared_ptr<Model>& model);
		void RasterizeModelWithoutIndices(const std::shared_ptr<Model>& model);
		void RasterizeTriangle(const glm::vec3& vertex_0, const glm::vec3& vertex_1, const glm::vec3& vertex_2);

	private:
		std::vector<std::weak_ptr<Model>> m_models;

		std::uint32_t m_window_width;
		std::uint32_t m_window_height;

		std::uint8_t* m_pixel_data;

		glm::vec4 m_clear_color;
	};
}