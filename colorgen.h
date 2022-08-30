#ifndef COLORGEN_H
#define COLORGEN_H

#include <iostream>

#include <list>
#include <queue>
#include <string>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "color.h"

class ColorGen
{
public:
	ColorGen(std::queue <Color>& colorQueue);

	~ColorGen();

	void start();

	void stop();

	void setPeriodGen(int periodGen);

	void setMutex(std::mutex* m);

	const std::list<Color>& getBackupList() const;

private:
	std::queue<Color>& _colorQueue;
	std::list<Color> _backupColorList;
	std::thread _currentThread;
	std::mutex* _m;
	std::condition_variable _cv;
	std::atomic<bool> _run = false;

	std::atomic<int> _periodGen = 500;

	void loop();
};

#endif // COLORGEN_H
