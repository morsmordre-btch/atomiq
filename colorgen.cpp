#include "colorgen.h"

ColorGen::ColorGen(std::queue <Color>& colorQueue) :
				   _colorQueue(colorQueue)
{
}

ColorGen::~ColorGen()
{
	_run = false;
};

void ColorGen::start()
{
	if (!_run)
	{
		_currentThread = std::thread(&ColorGen::loop, this);
		_run = true;
	}
	else
	{
		std::cerr << "GEN THREAD ALREADY WORK" << std::endl;
	}
}

void ColorGen::stop()
{

	if (_run)
	{
		std::cout << "STOPIN COLOR GEN THREAD" << std::endl;
		_run = false;
		_currentThread.join();
	}
}

void ColorGen::setMutex(std::mutex* m)
{
	_m = m;
}

void ColorGen::setPeriodGen(int periodGen)
{
	_periodGen = periodGen;
}

const std::list<Color>& ColorGen::getBackupList() const
{
	return _backupColorList;
}

void ColorGen::loop()
{
	std::cout << "START COLOR GEN THREAD" << std::endl;

	constexpr size_t maxSizeQueue = 10000;

	try
	{
		while(_run)
		{
			if ((_colorQueue.size() < maxSizeQueue))
			{
				std::scoped_lock lock(*_m);
				_colorQueue.emplace(static_cast<Colors>(std::rand() % 3));
				_backupColorList.push_back(_colorQueue.back());
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(_periodGen));
		}
	}
	catch (std::bad_alloc& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "STOP COLOR GEN THREAD" << std::endl;
}
