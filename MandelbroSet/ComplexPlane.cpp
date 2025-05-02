#include "ComplexPlane.h" //omg
#include <cmath>
#include <sstream>
#include <complex>

//#include <SFML/Graphics.hpp> // redundant(?) since h file contains this

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = (pixelHeight, pixelWidth) + (pixelHeight % pixelWidth); // pH = 540, pW = 960 (540, 960) + (540) tbh not sure of this formula
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()//WIP
{
	int pixelHeight = m_pixel_size.y;
	int pixelWidth = m_pixel_size.x;

	if (m_state == State::CALCULATING)
	{
		for (int j = 0; j < pixelWidth; j++) // j is for x
		{
			Uint8 r, g, b;
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;

			for (int i = 0; i < pixelHeight; i++)//i is for y
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };
				m_vArray[j + i * pixelWidth].color = { r, g, b };
			}
		}
	}
	m_state = State::DISPLAYING;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { xSize, ySize };
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { xSize, ySize };
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	//use mapPixelToCoords to find the Vector2f coord
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text) // is given a Text obj
{
	//stringstream bruh
	ostringstream s;
	s << "Mandelbro Set" << endl
	  << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl
	  << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
	  << "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
	text.setString(s.str());
}

size_t ComplexPlane::countIterations(Vector2f coord) //honestly who knows tbh
{
	//count
	size_t counter = 0;
	complex<double> c = {coord.x, coord.y};
	complex<double> z = c;
	while (abs(z) < 2.0 && counter < MAX_ITER)
	{
		z = z * z + c;
		counter++;
	}
	return counter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	//something
	const int range = 255;
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count < range)
	{
		r = 30;
		g = 40;
		b = 80;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	// assuming monitor is 1080p
	//x = [0,1920], 0 is a, 1920 is b
	//y = [1080,0], 1080 is a, 0 is b
	//pixel location (960,540) maps to (0,0) on complex plane
	int pixelWidth = m_pixel_size.y;
	int pixelHeight = m_pixel_size.x;
}