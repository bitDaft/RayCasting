/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <assert.h>


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	m_player(m_map)
{
	std::wstring floorLayout;
	const int dim = 32;

	floorLayout += L"################################";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..........#..........#........#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#.................###########..#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#.#########....................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#..............................#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#......#######...........##....#";
	floorLayout += L"#......#######...........##....#";
	floorLayout += L"#......#######...........##....#";
	floorLayout += L"#......#######...........##....#";
	floorLayout += L"#......#######...........##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"#........................##....#";
	floorLayout += L"################################";
	
	m_map = MAP(floorLayout, dim);
	tp1 = tp2 = std::chrono::system_clock::now();
	mouseX = 0;
	hwnd = FindWindowW(NULL, L"FakeRay");
	assert(hwnd != NULL);
	pt.x = 1366 / 2;
	pt.y = 768 / 2;
	
}

void Game::Go()
{
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<double> elt = tp2 - tp1;
	tp1 = tp2;

	gfx.BeginFrame();	
	UpdateModel(elt.count());
	ComposeFrame();
	gfx.EndFrame();

}

void Game::UpdateModel(double timePassed)
{

	if (captureMouse)
	{
		
		double val = 2.0;
		 
		int dir = 0;
		tempX = wnd.mouse.GetPosX();
		tempY = wnd.mouse.GetPosY();
		pt2.x = tempX;
		pt2.y = tempY;
		ClientToScreen(hwnd, &pt2);
		
		dir = pt2.x - pt.x;

		if (dir < 0)
		{
			m_player.moveStep(RENDERER::Movement::ROTATE_LEFT, (abs(dir) / val) * timePassed);
		}
		else if (dir > 0)
		{
			m_player.moveStep(RENDERER::Movement::ROTATE_RIGHT, (abs(dir) / val) * timePassed);
		}
		
		SetCursorPos(pt.x, pt.y);
	}
	if (wnd.kbd.KeyIsPressed('P'))
	{
		captureMouse = !captureMouse;
		tempX = wnd.mouse.GetPosX();
		tempY = wnd.mouse.GetPosY();
		pt.x = tempX;
		pt.y = tempY;
		ClientToScreen(hwnd, &pt);
		SetCursorPos(pt.x, pt.y);		
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		m_player.moveStep(RENDERER::Movement::STRAFE_LEFT, timePassed);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		m_player.moveStep(RENDERER::Movement::STRAFE_RIGHT, timePassed);
	}
	if (wnd.kbd.KeyIsPressed('W'))
	{
		m_player.moveStep(RENDERER::Movement::FORWARD, timePassed);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		m_player.moveStep(RENDERER::Movement::BACKWARD, timePassed);
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{
		m_player.moveStep(RENDERER::Movement::ROTATE_LEFT, timePassed);
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		m_player.moveStep(RENDERER::Movement::ROTATE_RIGHT, timePassed);
	}
}

void Game::ComposeFrame()
{
	m_player.render(gfx);
}
