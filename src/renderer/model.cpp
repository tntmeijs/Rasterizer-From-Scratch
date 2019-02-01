#include "renderer/model.hpp"

sr::Model::Model()
	: m_vertex_data_size(0)
	, m_index_data_size(0)
{
}

void sr::Model::Create(const std::shared_ptr<Vertex[]> vertex_data, const std::shared_ptr<std::int32_t> index_data, size_t vertex_data_size, size_t index_data_size) noexcept
{
	// Store vertex and index data as weak pointers
	m_vertex_data = vertex_data;
	m_index_data = index_data;

	// Store the size of the data arrays
	m_vertex_data_size = vertex_data_size;
	m_index_data_size = index_data_size;
}
