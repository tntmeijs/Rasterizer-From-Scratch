#pragma once

#include <glm/glm.hpp>

// Namespace sr --> "software rasterizer"
namespace sr
{
	struct Vertex
	{
		Vertex()
		{
			this->position = { 0.0, 0.0, 0.0 };
		}

		Vertex(double x, double y, double z)
		{
			this->position = { x, y, z };
		}

		glm::vec3 position;
	};
}