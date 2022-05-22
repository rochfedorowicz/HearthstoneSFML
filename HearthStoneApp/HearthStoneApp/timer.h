#pragma once
#ifndef TIMER
#define TIMER
#include <chrono>
#include <thread>
#include <semaphore>

class Timer {

	int maxSeconds, currentSeconds;

	bool shouldStop, hasFinished;

	std::binary_semaphore workingStateSemaphore {1};

	void count();

public:

	Timer();

	void start();

	void restart();

	bool finished();

	void setMaxSeconds(int _maxSeconds);

	int getCurrentSeconds();

	int getMaxSeconds();

};
#endif