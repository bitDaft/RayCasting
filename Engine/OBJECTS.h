#pragma once

#include "Graphics.h"
#include "VECTOR.h"

class STATIC_OBJECTS
{
private:
	int width;
	int height;
	double asp_rat;

public:
	VECTOR2D pos;
	void Draw(Graphics &gfx, short x, double dist, double *buf);

	STATIC_OBJECTS() ;
	STATIC_OBJECTS& operator=(const STATIC_OBJECTS&) = default;
	STATIC_OBJECTS(const STATIC_OBJECTS&) = default;
	STATIC_OBJECTS(VECTOR2D a, int w, int h);
	~STATIC_OBJECTS();
};

