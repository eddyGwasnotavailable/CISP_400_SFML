#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <vector>

//using namespace sf;
//using namespace std;
int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width / 2; // on a 1920x1080 should be 960x540
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	//RenderStates states;
	//RenderWindow window(VideoMode(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2), "Mandelbro Set", Style::Default);

	//construct complex plane
	//construct font and text obj
	ComplexPlane complexPlane(pixelWidth, pixelHeight);

	Font font;
	font.loadFromFile("fonts/CoolveticaRg.otf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(Color::White);;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				Vector2i mousePosi = Mouse::getPosition(window);
				if (event.mouseButton.button == Mouse::Right)
				{
					complexPlane.zoomOut();
					complexPlane.setCenter(mousePosi);
				}
				else if (event.mouseButton.button == Mouse::Left)
				{
					complexPlane.zoomIn();
					complexPlane.setCenter(mousePosi);
				}

			}
			if (event.type == Event::MouseMoved)
			{
				//call setMouseLocation on the ComplexPlane obj to store the x,y pixel location of the mouse
				complexPlane.setMouseLocation(Mouse::getPosition(window));
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//call updateRender on the ComplexPlane obj
		//call loadText on the ComplexPlane obj
		complexPlane.updateRender();
		complexPlane.loadText(text);

		window.clear();
		//draw the ComplexPlane obj
		//complexPlane.draw(window, states);//wip
		window.draw(complexPlane);
		//draw the Text obj(s)
		window.draw(text);
		window.display();
	}
	return 0;
}