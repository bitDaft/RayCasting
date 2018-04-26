#include "MAP.h"

#include <assert.h>

wchar_t MAP::getMapPosChar(int x, int y) const
{
	assert(x < m_mapDimension && x >= 0);
	assert(y < m_mapDimension && y >= 0);
	assert(mapSet);
	return m_map[y * m_mapDimension + x];
}

MAP::MAP(const std::wstring & map, const int dim)
	:m_map(map),m_mapDimension(dim)
{
	mapSet = true;
}

MAP::~MAP()
{
}
