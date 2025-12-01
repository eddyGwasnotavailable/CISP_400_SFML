#include "ComplexPlane.h"
#include <cmath>
#include <sstream>
#include <complex>

//#include <SFML/Graphics.hpp> // redundant since h file contains this

//using namespace sf;
//using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
	m_plane_center = { 0, 0 };
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

void ComplexPlane::updateRender()
{
	if (m_state != State::CALCULATING)
		return;

	int pixelWidth = m_pixel_size.x;
	int pixelHeight = m_pixel_size.y;

	for (int y = 0; y < pixelHeight; y++)
	{
		for (int x = 0; x < pixelWidth; x++)
		{
			int index = x + y * pixelWidth;
			m_vArray[index].position = { (float)x, (float)y };
			Vector2f coord = mapPixelToCoords({ x, y });
			size_t count = countIterations(coord);

			Uint8 r, b, g;
			iterationsToRGB(count, r, g, b);

			m_vArray[index].color = sf::Color(r, g, b);
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

void ComplexPlane::loadText(Text& text) //cursor should update live as it moves, center when user clicks
{
	stringstream s;
	s << "Mandelbrot Set" << endl
		<< "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl
		<< "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
		<< "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
	text.setString(s.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	//count
	size_t counter = 0;
	complex<double> c = { coord.x, coord.y };
	complex<double> z = c;
	//while (abs(z) < 2.0 && counter < MAX_ITER)
	while ((z.real() * z.real() + z.imag() * z.imag()) < 4.0 && counter < MAX_ITER)
	{
		z = z * z + c;
		counter++;
	}
	return counter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)//WIP(?) maybe add more colors
{
	//r = (Uint8)(count * 8);
	//g = (Uint8)(count * 4);
	//b = (Uint8)(255 - count * 8)
	// (we can use this for color)
	const int range = 255;
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	r = (Uint8)(count * 8);
	g = (Uint8)(count * 4);
	b = (Uint8)(255 - count * 8);
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	// assuming monitor is 1080p
	//x = [0,1920], 0 is a, 1920 is b
	//y = [1080,0], 1080 is a, 0 is b
	//pixel location (960,540) maps to (0,0) on complex plane
	float pixelWidth = m_pixel_size.x;
	float pixelHeight = m_pixel_size.y;

	//plane boundaries
	float realMin = m_plane_center.x - m_plane_size.x / 2.0f;
	float realMax = m_plane_center.x + m_plane_size.x / 2.0f;
	float imageMin = m_plane_center.y - m_plane_size.y / 2.0f;
	float imageMax = m_plane_center.y + m_plane_size.y / 2.0f;

	float x = (((float)mousePixel.x - 0) / (pixelWidth - 0)) * (realMax - realMin) + realMin;
	float y = (((float)mousePixel.y - pixelHeight) / (0 - pixelHeight)) * (imageMax - imageMin) + imageMin;
	return { x, y };
}