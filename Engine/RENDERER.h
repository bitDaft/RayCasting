#pragma once

#include "Graphics.h"

#include "VECTOR.h"
#include "MAP.h"

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

public:

	bool DrawMap = false;

	void moveStep(Movement mov,double frameTime);
	void render(Graphics& gfx);

	RENDERER() = delete;
	RENDERER(MAP& map);
	~RENDERER();
};

