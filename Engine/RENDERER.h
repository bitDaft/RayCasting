#pragma once

#include "VECTOR.h"

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
	VECTOR2D m_velMovement;
	

	double m_viewAngle;
	double m_FOV;

public:

	bool DrawMap = false;

	void moveStep(Movement mov,double frameTime);
	void render();

	RENDERER();
	~RENDERER();
};

