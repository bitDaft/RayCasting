#pragma once

#include <iostream>


class MAP
{
private:

	std::wstring m_map;
	int m_mapDimension;

public:

	char getMapPosChar(int x,int y); // integral coords of the map - m_map[x][y]

	//TODO : implement this function
	void Draw(int x,int y); //Pixel location on screen

	MAP() = delete;
	MAP(const MAP&) = delete;
	MAP& operator=(const MAP&) = delete;
	MAP(const std::wstring& map, const int dim);
	~MAP();
};

