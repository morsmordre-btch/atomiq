#include "colorsort.h"

ColorSort::ColorSort(std::queue <Color>& colorQueue,
					 std::list<Color>& sortedColorList) :
					 _colorQueue(colorQueue),
					 _sortedColorList(sortedColorList)
{
}

ColorSort::~ColorSort()
{
	_run = false;
};

void ColorSort::start()
{
	if (!_run)
	{
		_currentThread = std::thread(&ColorSort::loop, this);
		_run = true;
	}
	else
	{
		std::cerr << "SORT THREAD ALREADY WORK" << std::endl;
	}
}

void ColorSort::stop()
{

	if (_run)
	{
		std::cout << "STOPIN COLOR SORT THREAD" << std::endl;
		_run = false;
		_currentThread.join();
	}
}

void ColorSort::setMutex(std::mutex* m)
{
	_m = m;
}

void ColorSort::loop()
{
	std::cout << "START COLOR SORT THREAD" << std::endl;
	int addIndexMiddle = 0;
	try
	{
		while(_run)
		{
			if (_colorQueue.size() > 0)
			{
				Color colo{Colors::Red};
				{
					std::scoped_lock lock(*_m);
					colo = _colorQueue.front();
					_colorQueue.pop();
				}

				Colors thisColor = colo.getColor();
				if (thisColor == _order[0])
				{
					_sortedColorList.push_front(colo);
					addIndexMiddle++;
				}
				else if (thisColor == _order[1])
				{
					_sortedColorList.insert(std::next(_sortedColorList.begin(),
											addIndexMiddle), colo);
				}
				else if (thisColor == _order[2])
				{
					_sortedColorList.push_back(colo);
				}
				else
				{
					std::cerr << "OUT OF RANGE" << std::endl;
				}
			}
		}
	}
	catch (std::bad_alloc& e)
	{
		std::cerr << e.what() << std::endl;
		stop();
	}
	std::cout << "STOP COLOR SORT THREAD" << std::endl;
}

bool ColorSort::setColorOrder(std::string colorOrder)
{
	constexpr std::array<char, 3> chColors = {'R', 'G', 'B'};

	if (colorOrder.size() != chColors.size())
	{
		std::cerr << "ERROR SET COLOR ORDER" << std::endl;
		return false;
	}

	constexpr std::array<Colors, 3> colors = {Colors::Red,
											  Colors::Green,
											  Colors::Blue};

	std::transform(colorOrder.cbegin(), colorOrder.cend(),
				   colorOrder.begin(), [](unsigned char c)
	{
		return std::toupper(c);
	});

	for (size_t i = 0; i < colorOrder.size(); i++)
	{
		std::string::size_type posOrder = colorOrder.find(chColors[i]);
		if (posOrder != std::string::npos)

		{
			_order[posOrder] = colors[i];
		}
		else
		{
			std::cerr << "ERROR SET COLOR ORDER" << std::endl;
			return false;
		}
	}

	return true;
}

