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

	struct Triangle
	{
		Triangle()
		{
			this->corner_0 = 0;
			this->corner_1 = 0;
			this->corner_2 = 0;
		}

		Triangle(std::uint32_t corner_0, std::uint32_t corner_1, std::uint32_t corner_2)
		{
			this->corner_0 = corner_0;
			this->corner_1 = corner_1;
			this->corner_2 = corner_2;
		}

		std::uint32_t corner_0;
		std::uint32_t corner_1;
		std::uint32_t corner_2;
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