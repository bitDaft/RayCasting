#include "MAP.h"

#include <assert.h>

wchar_t MAP::getMapPosChar(int x, int y) const
{
	assert(x < m_mapDimension && x >= 0);
	assert(y < m_mapDimension && y >= 0);
	assert(mapSet);
	return m_map[y * m_mapDimension + x];
}

void MAP::Draw(int offsetX, int offsetY, double pX, double pY, double A, Graphics & gfx) const
{
	assert(mapSet);
	Color aa = Colors::White;
	for (int i = 0; i < m_mapDimension; i++)
	{
		for (int j = 0; j < m_mapDimension; j++)
		{
			aa = Colors::White;
			if (getMapPosChar(j, i) == L'.')
				aa = Colors::Black;
			for (int q = 0; q < 5; q++)
				for (int w = 0; w < 5; w++)
				{
					gfx.PutPixel(offsetX + w + j * 5, offsetY + q + i * 5, aa);
				}
		}
	}
	
	int pxx = ((int((pX * 10))) % 10) / 2;
	int pyy = ((int((pY * 10))) % 10) / 2;
	pX = int(pX);
	pY = (int)pY;
	pX *= 5;
	pY *= 5;
	for (int i = -1; i < 1; i++)
		for (int j = -1; j < 1; j++)
			gfx.PutPixel(int(offsetX + pX + pxx + i), int(offsetY + pY + pyy + j), Colors::Red);

	double xx = cos(A) * 0.3;
	double yy = sin(A) * 0.3;
	xx *= 5;
	yy *= 5;
		
	gfx.PutPixel(int(offsetX + xx * 2 + pX + pxx), int(offsetY + yy * 2 + pY + pyy), Colors::Green);
	gfx.PutPixel(int(offsetX + xx * 4 + pX + pxx), int(offsetY + yy * 4 + pY + pyy), Colors::Green);
	gfx.PutPixel(int(offsetX + xx * 6 + pX + pxx), int(offsetY + yy * 6 + pY + pyy), Colors::Green);
	gfx.PutPixel(int(offsetX + xx * 8 + pX + pxx), int(offsetY + yy * 8 + pY + pyy), Colors::Green);
	
}

MAP::MAP(const std::wstring & map, const int dim)
	:m_map(map),m_mapDimension(dim)
{
	mapSet = true;
}

MAP::~MAP()
{
}
