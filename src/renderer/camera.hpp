#pragma once

// GLM
#include <glm/glm.hpp>

namespace sr
{
	class Camera
	{
	public:
		Camera();
		~Camera() = default;

		void Create(double field_of_view_degrees, double aspect_ratio, const glm::vec3& position, const glm::vec3& target) noexcept;
		void Update() noexcept;

		void SetFOV(double fov_degrees) noexcept;
		void SetAspectRatio(double aspect_ratio) noexcept;
		void SetPosition(const glm::vec3& position) noexcept;
		void SetTarget(const glm::vec3& target)	noexcept;

		void AddFOV(double degrees_to_add) noexcept;
		void AddPosition(const glm::vec3& position_to_add) noexcept;
		void AddTarget(const glm::vec3& target_to_add) noexcept;

		double GetFOV() const noexcept;
		double GetAspectRatio() const noexcept;
		
		const glm::vec3& GetPosition() const noexcept;
		const glm::vec3& GetTarget() const noexcept;

		const glm::mat4& GetProjectionMatrix() const noexcept;
		const glm::mat4& GetViewMatrix() const noexcept;

		glm::mat4 ConstructProjectionViewMatrix() const noexcept;

	private:
		glm::vec3 m_position;
		glm::vec3 m_target;

		glm::mat4 m_projection_matrix;
		glm::mat4 m_view_matrix;

		double m_fov;
		double m_aspect_ratio;
	};
}