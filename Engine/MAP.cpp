#include "MAP.h"

#include <assert.h>

char MAP::getMapPosChar(int x, int y)
{
	assert(x >= m_mapDimension || x < 0);
	assert(y >= m_mapDimension || y < 0);
	return m_map[y * m_mapDimension + x];
}

MAP::MAP()
{
}


MAP::MAP(const std::wstring & map, const int dim)
	:m_map(map),m_mapDimension(dim)
{
}

MAP::~MAP()
{
}
