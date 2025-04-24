// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	///text for user to understand what to do
	Font font;
	font.loadFromFile("fonts/ArcaneNine.otf");
		
	Text text;
	//Text text1;
	text.setFont(font);
	//text1.setFont(font);
	text.setString("Using the left mouse button, plot three dots that form a triangle. Then use the left mouse button one more time for a surprise");
	text.setCharacterSize(30);
	text.setFillColor(Color::White);
	//text1.setString("Let there be chaos for like 2 milliseconds... Sierpinski triangle");
	//text1.setCharacterSize(30);
	//text1.setFillColor(Color::White);

	text.setPosition(0, 0); //should be top left
	//text1.setPosition(0, 67);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); // the origin of the 4th dot
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			
			int userVertex = rand() % vertices.size(); //psuedo random between 0, 1, and 2. will pick one of the verticies in the vector
			Vector2f lastp(points[points.size() - 1].x, points[points.size() - 1].y);
			Vector2f midp((lastp.x + vertices[userVertex].x) / 2, (lastp.y + vertices[userVertex].y) / 2);
			points.push_back(midp);
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));//responsible for the size of the first three dots(border of triangle)
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		///TODO:  Draw points
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rectUser(Vector2f(5, 5));
			rectUser.setPosition(Vector2f(points[i].x, points[i].y));
			rectUser.setFillColor(Color::Yellow);
			window.draw(rectUser);
		}
		//testing
		//cout << "Points vertex size: " << points.size();
		window.draw(text);
		//window.draw(text1);
		window.display();
	}
}
