// Application
#include "renderer/model.hpp"
#include "renderer/rasterizer.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"
#include "utility.hpp"

// SFML
#include <SFML/Graphics.hpp>

// GLM
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	// Window used to visualize the rasterizer output
	sf::RenderWindow window(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::APPLICATION_NAME);

	// Texture that will hold the rasterizer pixel data
	sf::Texture rasterizer_output;

	// Create the output texture
	if (!rasterizer_output.create(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT))
		return -1;

	// Sprite used to display the output texture
	sf::Sprite final_output;
	final_output.setTexture(rasterizer_output);

	// Rasterizer itself
	sr::Rasterizer software_rasterizer;
	software_rasterizer.Initialize(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);
	software_rasterizer.SetClearColor(255, 255, 255, 255);

	// Vertex data for an indexed cube
	std::shared_ptr<sr::Vertex[]> cube_vertex_data(new sr::Vertex[8]);
	cube_vertex_data[0] = {  0.5, -0.5, -0.5 };
	cube_vertex_data[1] = {  0.5, -0.5,  0.5 };
	cube_vertex_data[2] = { -0.5, -0.5,  0.5 };
	cube_vertex_data[3] = { -0.5, -0.5, -0.5 };
	cube_vertex_data[4] = {  0.5,  0.5, -0.5 };
	cube_vertex_data[5] = {  0.5,  0.5,  0.5 };
	cube_vertex_data[6] = { -0.5,  0.5,  0.5 };
	cube_vertex_data[7] = { -0.5,  0.5, -0.5 };

	std::shared_ptr<sr::Triangle[]> cube_triangle_data(new sr::Triangle[12]);
	cube_triangle_data[0]	= { 1, 3, 0 };
	cube_triangle_data[1]	= { 7, 5, 4 };
	cube_triangle_data[2]	= { 4, 1, 0 };
	cube_triangle_data[3]	= { 5, 2, 1 };
	cube_triangle_data[4]	= { 2, 7, 3 };
	cube_triangle_data[5]	= { 0, 7, 4 };
	cube_triangle_data[6]	= { 1, 2, 3 };
	cube_triangle_data[7]	= { 7, 6, 5 };
	cube_triangle_data[8]	= { 4, 5, 1 };
	cube_triangle_data[9]	= { 5, 6, 2 };
	cube_triangle_data[10]	= { 2, 6, 7 };
	cube_triangle_data[11]	= { 0, 3, 7 };

	// Cube model
	std::shared_ptr<sr::Model> cube_model = std::make_shared<sr::Model>();
	cube_model->Create(cube_vertex_data, cube_triangle_data, 8 * sizeof(sr::Vertex), 12 * sizeof(sr::Triangle));

	// To test "instancing", a bunch of matrices are created here to render cube meshes at different positions in the scene
	const glm::mat4 identity(1.f);
	glm::mat4 matrix_0, matrix_1, matrix_2, matrix_3;

	matrix_0 = glm::translate(identity, glm::vec3( 0.0,  0.0,  1.0));
	matrix_0 = glm::rotate(matrix_0, glm::radians(20.0f), glm::vec3(0, 1, 0));
	
	matrix_1 = glm::translate(identity, glm::vec3(-4.0, 1.0, 0.0));
	matrix_1 = glm::rotate(matrix_1, glm::radians(90.0f), glm::vec3(1, 0, 0));
	
	matrix_2 = glm::translate(identity, glm::vec3(3.0, -1.0, 0.0));
	matrix_2 = glm::rotate(matrix_2, glm::radians(65.0f), glm::vec3(0, 1, 0));
	
	matrix_3 = glm::translate(identity, glm::vec3(0.0, 0.0, -2.0));
	matrix_3 = glm::rotate(matrix_3, glm::radians(37.5f), glm::vec3(0, 0, 1));

	// Add the model to the model vector in the rasterizer (effectively queuing it for rendering)
	// Four matrices are passed here, which means the renderer will "instance" the cube four times
	software_rasterizer.AddModel(cube_model, { matrix_0, matrix_1, matrix_2, matrix_3 });

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Render the scene and save the output in the output texture
		const sr::Pixel* const data = software_rasterizer.Render();

		// Cast the data to a format readable by SFML (data is an array of structs that hold 4 color components as uint8)
		rasterizer_output.update(reinterpret_cast<const std::uint8_t* const>(data));

		window.clear();
		window.draw(final_output);
		window.display();
	}

	return 0;
}