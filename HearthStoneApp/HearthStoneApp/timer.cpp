#include "timer.h"

Timer::Timer() {
	maxSeconds = currentSeconds = 0;
	shouldStop = hasFinished = false;
}

void Timer::count() {
	workingStateSemaphore.acquire();
	hasFinished = false;
	while (!shouldStop) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		++currentSeconds;
		if (currentSeconds >= maxSeconds) shouldStop = true;
	}
	shouldStop = false;
	hasFinished = true;
	currentSeconds = 0;
	workingStateSemaphore.release();
}

void Timer::start() {
	std::thread countingThread(&Timer::count, this);
	countingThread.detach();
}

void Timer::restart() {
	std::thread restartingThread([this]() {
		shouldStop = true;
		workingStateSemaphore.acquire();
		workingStateSemaphore.release();
		start();
		});
	restartingThread.detach();	
}

bool Timer::finished() {
	return hasFinished;
}

void Timer::setMaxSeconds(int _maxSeconds) {
	maxSeconds = _maxSeconds;
}

int Timer::getCurrentSeconds() {
	return currentSeconds;
}

int Timer::getMaxSeconds() {
	return maxSeconds;
}