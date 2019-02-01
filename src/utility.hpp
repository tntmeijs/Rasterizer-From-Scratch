#pragma once

// GLM
#include <glm/glm.hpp>

// C++ standard
#include <cstdint>

namespace utility
{
	glm::vec3 NDCToRasterSpace(const glm::vec3& position, std::uint32_t width, std::uint32_t height)
	{
		return glm::vec3(width * (position.x + 1.0) / 2.0, height * (position.y + 1.0f) / 2.0, 1.0);
	}
}