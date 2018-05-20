#include "OBJECTS.h"

#include "Colors.h"

void STATIC_OBJECTS::Draw(Graphics &gfx, short x, double dist, double *buf)
{
	double hh = (int)((Graphics::ScreenHeight / dist) * 2.0);
	int ff = (int)((Graphics::ScreenHeight / 2.0) + (Graphics::ScreenHeight / dist));
	int newHeight = (int)((double)height / ((double)Graphics::ScreenHeight / hh));

	int newWidth = (int)(newHeight / asp_rat);
	int left = (x - newWidth / 2);
	int top = (ff - newHeight);

	for (int i = 0; i < newWidth ; i++)
	{
		if (((i + left) < Graphics::ScreenWidth) && ((i + left) >= 0))
		{
			if (buf[i + left] >= dist)
			{
			//	buf[i + left] = dist;
				for (int j = 0; j < newHeight; j++)
				{
					if (((j + top) < Graphics::ScreenHeight) && ((j + top) >= 0))
					{
						if (fabs(newWidth/2- i-j) > j)
							gfx.PutPixel(i + left, j + top, Colors::MakeRGB(20 * newHeight, 20, 20));
						else
							break;
					}
				}
			}
		}
	}
}

STATIC_OBJECTS::STATIC_OBJECTS()
	:pos(0.0,0.0)
{
}

STATIC_OBJECTS::STATIC_OBJECTS(VECTOR2D a, int w, int h)
	:pos(a),width(w),height(h)
{
	asp_rat = height / width;
}


STATIC_OBJECTS::~STATIC_OBJECTS()
{
}
