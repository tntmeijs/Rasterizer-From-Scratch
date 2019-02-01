// Application
#include "renderer/model.hpp"
#include "renderer/rasterizer.hpp"
#include "renderer/structures.hpp"
#include "settings.hpp"

// SFML
#include <SFML/Graphics.hpp>

int main()
{
	// Window used to visualize the rasterizer output
	sf::RenderWindow window(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::APPLICATION_NAME);

	// Rasterizer itself
	sr::Rasterizer software_rasterizer;
	software_rasterizer.Initialize(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);

	// Vertex data for a triangle (3 vertices)
	std::shared_ptr<sr::Vertex[]> model_data(new sr::Vertex[3]);
	model_data[0] = { -0.5,  0.5, 0.0 };
	model_data[0] = {  0.5,  0.5, 0.0 };
	model_data[0] = {  0.0, -0.5, 0.0 };

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

		window.clear();
		window.display();
	}

	return 0;
}