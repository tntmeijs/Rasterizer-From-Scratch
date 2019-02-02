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

	struct Pixel;

	class Rasterizer
	{
	public:
		Rasterizer();
		~Rasterizer();

		void Initialize(std::uint32_t window_width, std::uint32_t window_height);

		// When more than one model matrix is passed, the model will be "instanced"
		void AddModel(const std::shared_ptr<Model>& model, const std::vector<glm::mat4>& model_matrices) noexcept;
		void SetClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
		const Pixel* const Render() noexcept;

	private:
		void ClearScreen();
		void RasterizeModelWithIndices(const std::shared_ptr<Model>& model, const glm::mat4& matrix);
		void RasterizeModelWithoutIndices(const std::shared_ptr<Model>& model, const glm::mat4& matrix);
		void RasterizeTriangle(const glm::vec3& vertex_0, const glm::vec3& vertex_1, const glm::vec3& vertex_2);

	private:
		std::vector<std::pair<std::weak_ptr<Model>, std::vector<glm::mat4>>> m_models;

		std::uint32_t m_window_width;
		std::uint32_t m_window_height;

		Pixel* m_frame_buffer;
		std::uint8_t m_clear_color[4];
	};
}