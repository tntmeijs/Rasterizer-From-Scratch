#pragma once

// Namespace sr --> "software rasterizer"
namespace sr
{
	struct Vertex
	{
		Vertex()
		{
			this->x = 0.0;
			this->y = 0.0;
			this->z = 0.0;
		}

		Vertex(double x, double y, double z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		// Position
		double x, y, z;
	};
}