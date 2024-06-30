#pragma once

#include <vector>
#include <string>

class Animation
{
public:
	Animation() = delete;
	Animation(size_t X_size, size_t Y_size) { xSize = X_size; ySize = Y_size; }
	Animation(bool FullScreen);
	~Animation() {}

	void BeginAnimation();

private:
	size_t xSize;
	size_t ySize;
	std::vector<std::string> vec;

	size_t generateCharPosition();
	std::string generateRow();
	void displayCanvas();
	void transformLastRow();
	void DeleteNotNeededRows();
	void DeleteNotNeededColumns();
};