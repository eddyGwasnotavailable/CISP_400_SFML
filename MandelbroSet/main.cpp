#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;
int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width / 2; // on a 1920x1080 should be 960x540
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Mandelbro Set", Style::Default);
	//RenderWindow window(VideoMode(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2), "Mandelbro Set", Style::Default);

	//construct complex plane
	//construct font and text obj
	Font font;
	font.loadFromFile("fonts/QuentonSerif.otf");
	Text title;
	//Text centerL;
	//Text cursorL;
	Text instruct1;
	Text instruct2;

	title.setFont(font);
	//centerL.setFont(font);
	//cursorL.setFont(font);
	instruct1.setFont(font);
	instruct2.setFont(font);
	
	//title.setString("Mandelbrot Set");
	//centerL.setString("Center: ");
	//cursorL.setString("Cursor: ");
	//instruct1.setString("Left-click to Zoom in");
	//instruct2.setString("Right-click to Zoom out");

	title.setFillColor(Color::White);
	instruct1.setFillColor(Color::White);
	instruct2.setFillColor(Color::White);
	
	title.setCharacterSize(25);
	instruct1.setCharacterSize(25);
	instruct2.setCharacterSize(25);
	
	//title.setPosition(0,0);
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
				if (event.mouseButton.button == Mouse::Left)
				{
					cout << "Left mB pressed" << endl;
					//WIP zoom in
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					//wip zoom out
				}

			}
			if (event.type == Event::MouseMoved)
			{
				//call setMouseLocation on the ComplexPlane obj to  store the x,y pixel location of the mouse click
			}
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//update?
		//call updateRender on the ComplexPlane obj
		//call loadText on the ComplexPlane obj

		//draw
		window.clear();
		//window.draw(...);
		//draw the ComplexPlane obj
		//draw the Text obj(s)
		window.display();
	}
	//whatever else i suppose

}