// Application
#include "rasterizer/rasterizer.hpp"
#include "settings.hpp"

// SFML
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::APPLICATION_NAME);

	sr::Rasterizer software_rasterizer;

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