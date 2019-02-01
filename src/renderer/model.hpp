#pragma once

// C++ standard
#include <cstdint>
#include <memory>

// Namespace sr --> "software rasterizer"
namespace sr
{
	struct Vertex;

	class Model
	{
	public:
		Model();
		~Model() = default;

		//! Create the model with the specified vertex data
		void Create(
			const std::shared_ptr<Vertex[]> vertex_data,
			const std::shared_ptr<std::int32_t> index_data,
			size_t vertex_data_size,
			size_t index_data_size) noexcept;

		const std::weak_ptr<Vertex[]>& GetVertexData() const noexcept;
		const std::weak_ptr<std::int32_t>& GetIndexData() const noexcept;

		size_t GetVertexDataSize() const noexcept;
		size_t GetIndexDataSize() const noexcept;

	private:
		std::weak_ptr<Vertex[]> m_vertex_data;
		std::weak_ptr<std::int32_t> m_index_data;

		size_t m_vertex_data_size;
		size_t m_index_data_size;
	};
}