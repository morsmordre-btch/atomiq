#ifndef COLORSORT_H
#define COLORSORT_H

#include <iostream>

#include <list>
#include <queue>
#include <string>
#include <array>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <algorithm>

#include "color.h"

class ColorSort
{
public:
	ColorSort(std::queue<Color>& colorQueue,
			  std::list<Color>& sortedColorList);

	~ColorSort();

	void start();

	void stop();

	void setMutex(std::mutex* m);

	bool setColorOrder(std::string colorOrder);

private:
	std::queue<Color>& _colorQueue;
	std::list<Color>& _sortedColorList;
	std::thread _currentThread;
	std::mutex* _m;
	std::condition_variable* _cv;
	std::atomic<bool> _run = false;

	std::array<Colors, 3> _order;

	void loop();
};

#endif // COLORSORT_H
