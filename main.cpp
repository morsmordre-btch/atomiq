#include "color.h"
#include "colorgen.h"
#include "colorsort.h"

std::mutex m;

int main()
{
	std::cout << "hello dungeon master" << std::endl;

	try
	{
		std::queue<Color> colorQueue;
		std::list<Color> sortedColorList;

		ColorGen colorGen(colorQueue);
		colorGen.setPeriodGen(500);

		std::string colorOrder;
		std::cout << "Enter color order (example 'RGB')" << std::endl;
		std::cin >> colorOrder;

		ColorSort colorSort(colorQueue, sortedColorList);
		colorSort.setColorOrder(colorOrder);

		std::cout << "Enter:" << std::endl <<
					 "1 - Start color Gen" << std::endl <<
					 "2 - Start color Sort" << std::endl <<
					 "9 - Stop color Gen" << std::endl <<
					 "0 - Stop Color Sort" << std::endl;
		int key = -1;
		bool run = true;
		bool gen = true;
		bool sort = true;
		while(run)
		{
			std::cin >> key;
			switch (key)
			{
			case 1 :
				colorGen.start();
				gen = true;
			break;

			case 2 :
				colorSort.start();
				sort = true;
			break;

			case 9 :
				gen = false;
				colorGen.stop();
			break;

			case 0 :
				sort = false;
				colorSort.stop();
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
	}
	catch(int e)
	{
		std::cout << "THROW " << e;
	}
	return 0;
}
