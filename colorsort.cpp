#include "colorsort.h"

ColorSort::ColorSort(std::queue <Color>& colorQueue,
					 std::list<Color>& sortedColorList) :
					 _colorQueue(colorQueue),
					 _sortedColorList(sortedColorList)
{
}

ColorSort::~ColorSort()
{
	_currentThread.join();
};

void ColorSort::start()
{
	_currentThread = std::thread(&ColorSort::loop, this);
}

void ColorSort::stop()
{
	run = false;
	std::cout << "STOP COLOR SORT THREAD" << std::endl;
}

void ColorSort::loop()
{
	std::cout << "START COLOR SORT THREAD" << std::endl;
	int addIndexMiddle = 0;
	while(run)
	{
		if (_colorQueue.size() > 0)
		{
			std::scoped_lock lock(mut);
			Color colo = _colorQueue.front();
			_colorQueue.pop();

			Colors thisColor = colo.getColor();
			if (thisColor == _frontColor)
			{
				_sortedColorList.push_front(colo);
				addIndexMiddle++;
			}
			else if (thisColor == _middleColor)
			{
				_sortedColorList.insert(std::next(_sortedColorList.begin(),
												  addIndexMiddle), colo);
			}
			else if (thisColor == _backColor)
			{
				_sortedColorList.push_back(colo);
			}
		}
	}
}

void ColorSort::setColorOrder(std::string colorOrder)
{
	for (auto it : colorOrder)
	{
		assert(it == 'R' || it == 'G' || it == 'B' ||
			   it == 'r' || it == 'g' || it == 'b');
	}

	int count = 0;
	Colors order[] = {_frontColor, _middleColor, _backColor};
	for (auto it : colorOrder)
	{
		if (it == 'R')
		{
			order[count++] = Colors::Red;
		}
		else if (it == 'G')
		{
			order[count++] = Colors::Green;
		}
		else if (it == 'B')
		{
			order[count++] = Colors::Blue;
		}
	}
	_frontColor = order[0];
	_middleColor = order[1];
	_backColor = order[2];
}

