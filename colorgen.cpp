#include "colorgen.h"

ColorGen::ColorGen(std::queue <Color>& colorQueue) : _colorQueue(colorQueue)
{
}

ColorGen::~ColorGen()
{
	_currentThread.join();
};

void ColorGen::start()
{
	_currentThread = std::thread(&ColorGen::loop, this);
}

void ColorGen::stop()
{
	run = false;
	std::cout << "STOP COLOR GEN THREAD" << std::endl;
}

void ColorGen::setPeriodGen(int periodGen)
{
	_periodGen = periodGen;
}

std::list<Color> ColorGen::getBackupList()
{
	return _backupColorList;
}

void ColorGen::loop()
{
	std::cout << "START COLOR GEN THREAD" << std::endl;
	size_t maxSizeQueue = 1000;
	while(run)
	{
		std::scoped_lock lock(mut);
		if ((_colorQueue.size() < maxSizeQueue))
		{
			_colorQueue.push(Colors(std::rand() % 3));
			_backupColorList.push_back(_colorQueue.back());
			std::this_thread::sleep_for(std::chrono::milliseconds(_periodGen));
		}
	}
}
