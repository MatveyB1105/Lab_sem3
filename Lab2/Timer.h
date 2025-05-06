#pragma once

#include <iostream>
#include <chrono>
#include <thread>

class Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;

public:
	Timer() {
		start = std::chrono::steady_clock::now();
	}
	void TimeStart() {
		start = std::chrono::steady_clock::now();
	}
	float GetTime() {
		std::chrono::time_point<std::chrono::steady_clock> time = std::chrono::steady_clock::now();
		std::chrono::duration<float> duration = time - start;
		return duration.count();
	}
	~Timer() {
	}
};