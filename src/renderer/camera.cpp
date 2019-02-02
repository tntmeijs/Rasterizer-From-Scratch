#include "camera.hpp"

// GLM (does not compile with -Wall / -WX)
#pragma warning(push)
#pragma warning(disable : 4127)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

sr::Camera::Camera()
	: m_position { 0.0, 0.0, 0.0 }
	, m_target { 0.0, 0.0, -1.0 }
	, m_projection_matrix(1.0)
	, m_view_matrix(1.0)
	, m_fov(glm::radians(80.0))
	, m_aspect_ratio(16.0 / 9.0)
{
}

void sr::Camera::Create(double field_of_view_degrees, double aspect_ratio, const glm::vec3 & position, const glm::vec3 & target) noexcept
{
	m_projection_matrix = glm::perspectiveRH(glm::radians(field_of_view_degrees), aspect_ratio, 0.1, 1000.0);
	m_view_matrix = glm::lookAtRH(position, target, glm::vec3(0, 1, 0));

	m_position = position;
	m_target = target;
}

void sr::Camera::Update() noexcept
{
	m_view_matrix = glm::lookAtRH(m_position, m_target, glm::vec3(0, 1, 0));
}

void sr::Camera::SetFOV(double fov_degree) noexcept
{
	m_fov = glm::radians(fov_degree);
}

void sr::Camera::SetAspectRatio(double aspect_ratio) noexcept
{
	m_aspect_ratio = aspect_ratio;
}

void sr::Camera::SetPosition(const glm::vec3& position) noexcept
{
	m_position = position;
}

void sr::Camera::SetTarget(const glm::vec3& target) noexcept
{
	m_target = target;
}

void sr::Camera::AddFOV(double degrees_to_add) noexcept
{
	m_fov += glm::radians(degrees_to_add);
}

void sr::Camera::AddPosition(const glm::vec3& position_to_add) noexcept
{
	m_position += position_to_add;
}

void sr::Camera::AddTarget(const glm::vec3& target_to_add) noexcept
{
	m_target += target_to_add;
}

double sr::Camera::GetFOV() const noexcept
{
	return m_fov;
}

double sr::Camera::GetAspectRatio() const noexcept
{
	return m_aspect_ratio;
}

const glm::vec3& sr::Camera::GetPosition() const noexcept
{
	return m_position;
}

const glm::vec3& sr::Camera::GetTarget() const noexcept
{
	return m_target;
}

const glm::mat4& sr::Camera::GetProjectionMatrix() const noexcept
{
	return m_projection_matrix;
}

const glm::mat4& sr::Camera::GetViewMatrix() const noexcept
{
	return m_view_matrix;
}

glm::mat4 sr::Camera::ConstructProjectionViewMatrix() const noexcept
{
	return m_projection_matrix * m_view_matrix;
}
