#include <sstream>
#include <iostream>

#include <list>
#include <queue>
#include <string>

#include <mutex>

#include "color.h"
#include "colorgen.h"
#include "colorsort.h"

int main()
{
	std::cout << "Hello atomiq" << std::endl;

	std::queue<Color> colorQueue;
	std::list<Color> sortedColorList;

	std::mutex m;

	ColorGen colorGen(colorQueue);
	colorGen.setMutex(&m);
	colorGen.setPeriodGen(200);

	std::string colorOrder;
	std::cout << "Enter color order (example 'RGB')" << std::endl;
	std::cin >> colorOrder;

	ColorSort colorSort(colorQueue, sortedColorList);
	colorSort.setMutex(&m);
	colorSort.setColorOrder(colorOrder);

	std::cout << "Enter:" << '\n' <<
				 "1 - Start Color Gen" << '\n' <<
				 "2 - Start Color Sort" << '\n' <<
				 "9 - Stop Color Gen" << '\n' <<
				 "0 - Stop Color Sort" << '\n' <<
				 "5 - Show" << std::endl;

	constexpr int START_GEN = 1;
	constexpr int START_SORT = 2;
	constexpr int STOP_GEN = 9;
	constexpr int STOP_SORT = 0;
	constexpr int SHOW = 5;

	bool run = true;
	bool gen = true;
	bool sort = true;
	while(run)
	{
		int key = -1;
		std::string str;
		std::getline(std::cin, str);

		if (str.empty())
		{
			continue;
		}

		auto isNumber = [](std::string& str)
		{
			for (auto it : str)
			{
				if (!std::isdigit(it))
				{
					return false;
				}
			}
			return true;
		};

		if (isNumber(str))
		{
			try
			{
				key = std::stoi(str);
			}
			catch (std::exception& e)
			{
				std::cout << "INCORECT INPUTI" << std::endl;
				continue;
			}
		}
		else
		{
			std::cout << "INCORECT INPUTI" << std::endl;
		}

		switch (key)
		{
		case START_GEN :
			colorGen.start();
			gen = true;
		break;

		case START_SORT :
			colorSort.start();
			sort = true;
		break;

		case STOP_GEN :
			gen = false;
			colorGen.stop();
		break;

		case STOP_SORT :
			sort = false;
			colorSort.stop();
		break;
		case SHOW :
		{
			std::scoped_lock lock(m);
			std::list<Color> unsortedColorList = colorGen.getBackupList();

			std::cout << std::endl << "UNSORTED: " << std::endl;

			for (auto it : unsortedColorList)
			{
				std::cout << " " << it << "\t";
			}

			std::cout << std::endl << "SORTED: " << std::endl;

			for (auto it : sortedColorList)
			{
				std::cout << " " << it << "\t";
			}
			std::cout << std::endl;
		}
		break;
		}

		if (!gen && !sort)
		{
			run = false;
		}
	}

	std::cout << std::endl << "UNSORTED: " << std::endl;

	std::list<Color> unsortedColorList = colorGen.getBackupList();

	for (auto it : unsortedColorList)
	{
		std::cout << " " << it << "\t";
	}

	std::cout << std::endl << "SORTED: " << std::endl;

	for (auto it : sortedColorList)
	{
		std::cout << " " << it << "\t";
	}
	std::cout << std::endl;

	return 0;
}
