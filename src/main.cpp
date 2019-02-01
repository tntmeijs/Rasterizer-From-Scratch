// Application
#include "renderer/model.hpp"
#include "renderer/rasterizer.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"
#include "utility.hpp"

// SFML
#include <SFML/Graphics.hpp>

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

	// Vertex data for a triangle (3 vertices)
	std::shared_ptr<sr::Vertex[]> model_data(new sr::Vertex[3]);
	model_data[0] = { -0.5,  0.5, 1.0 };
	model_data[1] = {  0.5,  0.5, 1.0 };
	model_data[2] = {  0.0, -0.5, 1.0 };

	// Convert the vertex positions from NDC to raster space
	model_data[0].position = utility::NDCToRasterSpace(model_data[0].position, settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);
	model_data[1].position = utility::NDCToRasterSpace(model_data[1].position, settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);
	model_data[2].position = utility::NDCToRasterSpace(model_data[2].position, settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);

	// Triangle "model"
	std::shared_ptr<sr::Model> triangle_model = std::make_shared<sr::Model>();
	triangle_model->Create(model_data, nullptr, 3 * sizeof(sr::Vertex), 0);

	// Add the triangle model to the model vector in the rasterizer (effectively queuing it for rendering)
	software_rasterizer.AddModel(triangle_model);

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