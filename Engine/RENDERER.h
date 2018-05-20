#pragma once

#include "Graphics.h"
#include "OBJECTS.h"

#include "VECTOR.h"
#include "MAP.h"
#include <list>

class RENDERER
{
public:
	enum class Movement
	{
		FORWARD,
		BACKWARD,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		STRAFE_LEFT,
		STRAFE_RIGHT,
		NO_MOVE
	};
private:
	VECTOR2D m_pos;
	double m_velMovement;
	double m_velRotate;
	
	double m_viewAngle;
	double m_FOV;

	const MAP& m_level;

	double zbuf[Graphics::ScreenWidth];

public:

	bool DrawMap = true;

	void moveStep(Movement mov,double frameTime);
	void render(Graphics& gfx, std::list<STATIC_OBJECTS> oo);

	RENDERER() = delete;
	RENDERER(MAP& map);
	~RENDERER();
};

