#ifndef COLORGEN_H
#define COLORGEN_H

#include "color.h"

class ColorGen
{
public:
	ColorGen(std::queue <Color>& colorQueue);

	~ColorGen();

	void start();

	void stop();

	void setPeriodGen(int periodGen);

	std::list<Color> getBackupList();

private:
	std::queue<Color>& _colorQueue;
	std::list<Color> _backupColorList;
	std::thread _currentThread;
	std::atomic<bool> run = true;

	int _periodGen = 500;

	void loop();
};

#endif // COLORGEN_H
