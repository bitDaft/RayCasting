#include "RENDERER.h"
#include "Colors.h"

#include <cmath>
#include <algorithm>

#define pi 3.14159265359

void RENDERER::moveStep(Movement mov, double frameTime)
{
	switch (mov)
	{
	case Movement::ROTATE_LEFT:
		m_viewAngle -= ((m_velRotate * 0.5) * frameTime);
		break;
	case Movement::ROTATE_RIGHT:
		m_viewAngle += ((m_velRotate * 0.5) * frameTime);
		break;
	case Movement::FORWARD: {
		VECTOR2D temp = ((VECTOR2D(cos(m_viewAngle), sin(m_viewAngle)) * m_velMovement) * frameTime);
		m_pos = m_pos + temp;
		if (m_level.getMapPosChar((int)m_pos.getX(), (int)m_pos.getY()) == L'#')
			m_pos = m_pos - temp;

		break;
		}
	case Movement::BACKWARD:{
		VECTOR2D temp = ((VECTOR2D(cos(m_viewAngle), sin(m_viewAngle)) * m_velMovement) * frameTime);
		m_pos = m_pos - temp;
		if (m_level.getMapPosChar((int)m_pos.getX(), (int)m_pos.getY()) == L'#')
			m_pos = m_pos + temp;

		break;
		}
	case Movement::STRAFE_LEFT: {
		VECTOR2D temp = ((VECTOR2D(sin(m_viewAngle), -cos(m_viewAngle)) * m_velMovement) * frameTime);
		m_pos = m_pos + temp;
		if (m_level.getMapPosChar((int)m_pos.getX(), (int)m_pos.getY()) == L'#')
			m_pos = m_pos - temp;

		break;
		}
	case Movement::STRAFE_RIGHT: {
		VECTOR2D temp = ((VECTOR2D(-sin(m_viewAngle), cos(m_viewAngle)) * m_velMovement) * frameTime);
		m_pos = m_pos + temp;
		if (m_level.getMapPosChar((int)m_pos.getX(), (int)m_pos.getY()) == L'#')
			m_pos = m_pos - temp;

		break;
		}
	}
	if (m_viewAngle >= 2 * pi)
	{
		m_viewAngle -= 2 * pi;
	}
}

void RENDERER::render(Graphics & gfx)
{
	double rayAngle = 0.0;
	const double fovUnit = (m_FOV / double(Graphics::ScreenWidth));
	const double stepSize = 0.1;

	for (int x = 0; x < Graphics::ScreenWidth; x++)
	{
		rayAngle = (m_viewAngle - m_FOV/2.0) + (double(x) * fovUnit);

		VECTOR2D uRay(cos(rayAngle), sin(rayAngle));
	
		bool hitWall = false;
		double distance = 0.0;

		while (!hitWall && distance < 16.0)
		{
			distance += stepSize;
			VECTOR2D Ray = uRay * distance;
			VECTOR2D pos = m_pos + Ray;

			if (m_level.getMapPosChar((int)pos.getX(), (int)pos.getY()) == L'#')
			{
				hitWall = true;
			}
		}

		int CeilingEnd = (int)((Graphics::ScreenHeight / 2.0) - (Graphics::ScreenHeight / distance));
		int floorStart = Graphics::ScreenHeight - CeilingEnd;

		for (int y = 0; y < Graphics::ScreenHeight; y++)
		{
			if (y < CeilingEnd)
			{
				gfx.PutPixel(x, y, Colors::Black);
			}
			else if (y <= floorStart)
			{
				unsigned char pp = 255;//std::min(255,int((255 / distance) * 0.5));

				gfx.PutPixel(x, y, Colors::MakeRGB(pp, pp, pp));
			}
			else
			{
				gfx.PutPixel(x, y, Colors::MakeRGB(0,255,0));
			}
		}
	}
}

RENDERER::RENDERER(MAP & map)
	:m_pos(8.0,8.0),m_velMovement(5.0),m_level(map),m_viewAngle(0.0),m_FOV(40*(pi / 180)),m_velRotate(5.0)
{
}


RENDERER::~RENDERER()
{
}
