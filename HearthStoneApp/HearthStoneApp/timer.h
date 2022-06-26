#pragma once
#ifndef TIMER
#define TIMER
#include <chrono>
#include <thread>
#include <semaphore>

/** Class implemented for time measurement. */
class Timer {

	/** Maximum and current amount of seconds. */
	int maxSeconds, currentSeconds;

	/** Logic values indicating if timer should be stopped and if has finished. */
	bool shouldStop, hasFinished;

	/** Binary semaphore used for restarting timer. */
	std::binary_semaphore workingStateSemaphore {1};

	/** Function that counts time. Works as thread. */
	void count();

public:

	/** Default constructor. */
	Timer();

	/** Function that starts counting. */
	void start();

	/** Function restarting timer. */
	void restart();

	/** Funtion checking if timer has finished counting. */
	bool finished();

	/** Maximum amount of seconds setter. */
	void setMaxSeconds(int _maxSeconds);

	/** Getter for current amount of seconds. */
	int getCurrentSeconds();

	/** Getter for maximum amount of seconds. */
	int getMaxSeconds();

};
#endif