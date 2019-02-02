#pragma once

// GLM
#include <glm/glm.hpp>

// C++ standard
#include <cstdint>
#include <tuple>
#include <utility>

namespace utility
{
	// Additional arguments used in this vertex shader:
	// 0: model matrix
	// 1: projection-view matrix
	template<typename... Args>
	inline glm::vec4 VertexShader(const glm::vec3& vertex, Args&&... args)
	{
		auto input = std::make_tuple(std::forward<Args>(args)...);

		// Retrieve the vertex shader data
		const auto& model_matrix	= std::get<0>(input);
		const auto& pv_matrix		= std::get<1>(input);

		glm::vec4 vertex_output = pv_matrix * model_matrix * glm::vec4(vertex, 1.0);

		return vertex_output;
	}

	inline void ConvertClipToRasterSpace(glm::vec4& position, const glm::vec2& viewport_size)
	{
		position = glm::vec4(viewport_size.x * (position.x + position.w) / 2.0, viewport_size.y * (position.w - position.y) / 2.0, position.z, position.w);
	}
}