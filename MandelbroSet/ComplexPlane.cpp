#include "ComplexPlane.h" //omg 

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

void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int j = 0; j < ) // j is for x
		{
			for (int i = 0; i < )//i is for y
			{
				//wip
			}
		}
	}
}