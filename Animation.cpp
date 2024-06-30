#pragma once

#include "Animation.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>

Animation::Animation(bool FullScreen)
{
	AllocConsole();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		xSize = csbi.dwSize.X;
		ySize = csbi.dwSize.Y-1;
	}
	else {
		std::cerr << "Failed to get console screen buffer info." << std::endl;
	}
}

void Animation::BeginAnimation()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	while (true)
	{
		size_t vecSize = vec.size();
		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) 
		{
			xSize = csbi.dwSize.X;
			ySize = csbi.dwSize.Y - 1;
		}

		vec.emplace(vec.begin(), generateRow());
		/*
		std::wstring debug = L"xSize: " + std::to_wstring(xSize) + L" ySize: " + std::to_wstring(ySize) +
			L" VecSize: " + std::to_wstring(vecSize) + L" RowSize: " + std::to_wstring(vec[vec.size() - 1].size()) + L"\n";
		OutputDebugString(debug.c_str());
		*/

		if (vec[vec.size() - 1].size() > xSize)
			DeleteNotNeededColumns();
		if (vecSize > ySize)
			DeleteNotNeededRows();
		if (vecSize > ySize - 1)
		{
			transformLastRow();
			vec.pop_back();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		displayCanvas();
	}
}

size_t Animation::generateCharPosition()
{
	size_t ind = rand() % xSize;
	return ind;
}

std::string Animation::generateRow()
{
	size_t ind = generateCharPosition();

	std::string row;
	for (size_t i = 0; i < xSize; i++)
	{
		row += ' ';
	}
	row[ind] = '|';
	return row;
}

void Animation::displayCanvas()
{
	system("cls");
	std::string canvas;
	for (auto row : vec)
		canvas += row + "\n";
	std::cout << canvas;
}

void Animation::transformLastRow()
{
	std::string last = vec.at(vec.size() - 1);
	std::string beforeLast = vec.at(vec.size() - 2);
	for (size_t i = 0; i < last.size(); i++)
	{
		if (last[i] == '|')
			beforeLast[i] = generateCharPosition() > last.size() / 2 ? 'v' : 'V';
	}
	vec.at(vec.size() - 2) = beforeLast;
}

void Animation::DeleteNotNeededRows()
{
	size_t notNeededRows = vec.size() - ySize;
	vec.erase(vec.begin(), vec.begin()+notNeededRows);
}

void Animation::DeleteNotNeededColumns()
{
	for (auto& row : vec)
		row.resize(xSize);
}