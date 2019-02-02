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
	class Camera;

	struct Pixel;

	class Rasterizer
	{
	public:
		Rasterizer();
		~Rasterizer();

		void Initialize(std::uint32_t window_width, std::uint32_t window_height);
		void Update() const noexcept;
		void ClearScreen();

		// When more than one model matrix is passed, the model will be "instanced"
		void AddModel(const std::shared_ptr<Model>& model, const std::vector<glm::mat4>& model_matrices) noexcept;
		const int AddCamera(double field_of_view_degrees, double aspect_ratio, const glm::vec3& position, const glm::vec3& target) noexcept;

		void RemoveCamera(int index) noexcept;

		void SetClearColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept;
		void SetActiveCameraIndex(unsigned int index) noexcept;

		const int GetActiveCameraIndex() const noexcept;

		const Pixel* const Render() noexcept;

	private:
		void RasterizeModelWithIndices(const std::shared_ptr<Model>& model, const glm::mat4& model_matrix, const glm::mat4& projection_view_matrix);
		void RasterizeModelWithoutIndices(const std::shared_ptr<Model>& model, const glm::mat4& model_matrix, const glm::mat4& projection_view_matrix);
		void RasterizeTriangle(const glm::vec4& vertex_0, const glm::vec4& vertex_1, const glm::vec4& vertex_2);

	private:
		std::vector<std::pair<std::weak_ptr<Model>, std::vector<glm::mat4>>> m_models;
		std::vector<std::shared_ptr<Camera>> m_cameras;

		int m_active_camera_index;

		std::uint32_t m_window_width;
		std::uint32_t m_window_height;

		Pixel* m_frame_buffer;
		std::uint8_t m_clear_color[4];
	};
}