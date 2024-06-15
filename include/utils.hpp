#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <random>


typedef std::chrono::time_point<std::chrono::system_clock> timePoint_t;
typedef std::chrono::duration<double> duration_t;

namespace Utils
{

#ifdef _WIN32
	constexpr const char* CLEAR_SCREEN = "cls";
#else
	constexpr const char* CLEAR_SCREEN = "clear";
#endif

	bool file_exists_t(const char* p_file_name);
	void clear_screen();
	void display_error(const char* p_error);
	std::string current_time();
	unsigned int generate_id();
	unsigned int randInt(int pMin, int pMax);
};

