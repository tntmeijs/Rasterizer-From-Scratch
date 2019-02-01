#pragma once

// GLM
#include <glm/glm.hpp>

// C++ standard
#include <cstdint>

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

	struct Pixel
	{
		Pixel()
		{
			this->r = 0;
			this->g = 0;
			this->b = 0;
			this->a = 0;
		}

		Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		std::uint8_t r, g, b, a;
	};
}