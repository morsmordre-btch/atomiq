#ifndef COLORSORT_H
#define COLORSORT_H

#include "color.h"

class ColorSort
{
public:
	ColorSort(std::queue<Color>& colorQueue,
			  std::list<Color>& sortedColorList);

	~ColorSort();

	void start();

	void stop();

	void setColorOrder(std::string colorOrder);

private:
	std::queue<Color>& _colorQueue;
	std::list<Color>& _sortedColorList;
	std::thread _currentThread;
	std::atomic<bool> run = true;

	Colors _frontColor = Colors::Red;
	Colors _middleColor = Colors::Green;
	Colors _backColor = Colors::Blue;

	void loop();
};

#endif // COLORSORT_H
