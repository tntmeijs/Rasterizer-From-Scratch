#pragma once

// C++ standard
#include <cstdint>
#include <memory>

// Namespace sr --> "software rasterizer"
namespace sr
{
	struct Vertex;
	struct Triangle;

	class Model
	{
	public:
		Model();
		~Model() = default;

		//! Create the model with the specified vertex data
		void Create(
			const std::shared_ptr<Vertex[]>& vertex_data,
			const std::shared_ptr<Triangle[]>& triangle_data,
			size_t vertex_data_size,
			size_t index_data_size) noexcept;

		const std::weak_ptr<Vertex[]>& GetVertexData() const noexcept;
		const std::weak_ptr<Triangle[]>& GetIndexData() const noexcept;

		size_t GetVertexDataSize() const noexcept;
		size_t GetIndexDataSize() const noexcept;

	private:
		std::weak_ptr<Vertex[]> m_vertex_data;
		std::weak_ptr<Triangle[]> m_index_data;

		size_t m_vertex_data_size;
		size_t m_index_data_size;
	};
}