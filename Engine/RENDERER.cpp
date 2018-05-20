#include "RENDERER.h"
#include "Colors.h"

#include <cmath>
#include <utility>

#define pi 3.14159265359

struct objr
{
	double dist;
	unsigned short ang;
};

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
	if (m_viewAngle > pi)
	{
		m_viewAngle -= 2 * pi;
	}
	else if (m_viewAngle < -pi)
	{
		m_viewAngle += 2 * pi;
	}
}

void RENDERER::render(Graphics & gfx,std::list<STATIC_OBJECTS> oo)
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

		bool isEdge = false;

		while (!hitWall)
		{
			distance += stepSize;
			VECTOR2D Ray = uRay * distance;
			VECTOR2D pos = m_pos + Ray;

			if (m_level.getMapPosChar((int)pos.getX(), (int)pos.getY()) == L'#')
			{
				hitWall = true;
				
				VECTOR2D edgePos = VECTOR2D((int)pos.getX(),(int)pos.getY());

				for (int tx = 0; tx < 2; tx++)
					for (int ty = 0; ty < 2; ty++)
					{
						VECTOR2D pToEdge = edgePos + VECTOR2D((double)tx-0.0005, (double)ty-0.0005) - m_pos;
						double tempD = pToEdge.getDistance();
						if ((tempD >= (distance-0.5)) && (tempD <= (distance + 0.5)))
						{		
							if (acos(uRay.Dot(pToEdge.getUnitVector())) < 0.001)
							{
								isEdge = true;
								goto jmp;
							}
						}
					}
			jmp:;
			}
		}
		
		zbuf[x] = distance;
		int CeilingEnd = (int)((Graphics::ScreenHeight / 2.0) - (Graphics::ScreenHeight / distance));
		int floorStart = Graphics::ScreenHeight - CeilingEnd;

		for (int y = 0; y < Graphics::ScreenHeight; y++)
		{
			if (y < CeilingEnd)
			{
				//gfx.PutPixel(x, y, Colors::Black);
				double pp = (Graphics::ScreenHeight / 2.2) - y;
				pp *= 2.0;

				if (pp < 0) pp = 0.0;
				if (pp > 255) pp = 255.0;

				double r = (80 * pp) / 255;// 0-176

				gfx.PutPixel(x, y, Colors::MakeRGB((unsigned char)r, (unsigned char)r, (unsigned char)r));
				//gfx.PutPixel(x, y, Colors::MakeRGB(pp,pp,pp));
			}
			else if (y <= floorStart )
			{
				int pp;// = std::min(255, int((255 / distance) * 2.5));

				pp = int(63 / (distance /35));
				if (pp < 0)pp = 0;
				if (pp > 255)pp = 255;
				/*if (distance > 18) pp = 63/2;
				else if (distance > 16) pp = 63;
				else if (distance > 14) pp = 63 * 2;
				else if (distance > 11) pp = 63 * 2.5;
				else if (distance > 8) pp = 63 * 3;
				else pp = 212;*/
				/*
				as distance decreased the multiplier increases 63 * mult;mult start from 1/5;
				*/
				if (isEdge || y > floorStart-2 || y == CeilingEnd) pp = 0;
				
				gfx.PutPixel(x, y, Colors::MakeRGB(pp, pp, pp));
				
			}
			else
			{
				double pp = y - Graphics::ScreenHeight / 2.2;
				pp *= 2.0;

				if (pp < 0) pp = 0.0;
				if (pp > 255) pp = 255.0;
				
				double r = (79*pp)/255;// 0-176
				double g = (30*pp)/255;
				double b = (1*pp)/255;
				
				gfx.PutPixel(x, y, Colors::MakeRGB((unsigned char)r, (unsigned char)g, (unsigned char)b));
			}
		}
	}

	std::list<std::pair< STATIC_OBJECTS&, const objr>> a;

	for (auto &obj : oo)
	{
		VECTOR2D po = obj.pos - m_pos;
		double ang = m_viewAngle - atan2(po.getY(), po.getX());
		if (ang < -pi)
			ang += 2.0 * pi;
		if (ang > pi)
			ang -= 2.0 * pi;

		bool bInFOV = fabs(ang) < ((m_FOV + 10.0) / 2.0);

		if (bInFOV && po.getDistance() > 1.0)
		{
			unsigned short locx = (int)(((0.5 * (-ang / (m_FOV / 2.0))) + 0.5) * (double)Graphics::ScreenWidth);
			a.push_back(std::pair< STATIC_OBJECTS&, const objr>(obj, { po.getDistance() ,locx }));
			//obj.Draw(gfx, locx, po.getDistance(), zbuf);
		}
	}
	a.sort([](const std::pair< STATIC_OBJECTS&, const objr> &a, const std::pair< STATIC_OBJECTS&, const objr> &b)
	{
		return  a.second.dist > b.second.dist;
	});
	for (auto &obj : a)
	{
		obj.first.Draw(gfx, obj.second.ang, obj.second.dist, zbuf);
	}

	if (DrawMap)
		m_level.Draw(10, 10, m_pos.getX(), m_pos.getY(), m_viewAngle, gfx);
}

RENDERER::RENDERER(MAP & map)
	:m_pos(16.0,16.0),m_velMovement(5.5),m_level(map),m_viewAngle(0.0),m_FOV(35*(pi / 180)),m_velRotate(1.5)
{
}


RENDERER::~RENDERER()
{
}
