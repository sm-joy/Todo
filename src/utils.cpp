#include "../include/utils.hpp"

void Utils::clear_screen() { system(CLEAR_SCREEN); }

void Utils::display_error(const char* p_error)
{
	std::cout
		<< "\n     Error Mode     "
		<< "\n===================="
		<< "\n Error: "
		<< p_error
		<< "\n===================="
		<< "\n Press Enter to exit view mode...";
	std::cin.get();
}

std::string Utils::current_time()
{
	timePoint_t now = std::chrono::system_clock::now();
	time_t now_tm = std::chrono::system_clock::to_time_t(now);
	std::tm current_time;

#ifdef _WIN32
	localtime_s(&current_time, &now_tm);
#else
	localtime_r(&current_time, &now_tm);
#endif
	

	std::ostringstream oss;
	oss 
		<< "(" << (current_time.tm_year + 1900) << "-"
		<< (current_time.tm_mon + 1) << "-"
		<< current_time.tm_mday << " "
		<< current_time.tm_hour << ":"
		<< current_time.tm_min << ":"
		<< current_time.tm_sec << ")";

	return oss.str();
}

unsigned int Utils::generate_id()
{
	timePoint_t now = std::chrono::system_clock::now();
	long long now_s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
	unsigned int id = (now_s % 100) * 100000 + randInt(10000, 99999);
	return id;
}


bool Utils::file_exists_t(const char* p_file_name)
{
	std::ifstream file(p_file_name);
	bool exists = file.good();
	file.close();
	return exists;
}

unsigned int Utils::randInt(int pMin, int pMax)
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());

	std::uniform_int_distribution<unsigned int> distribution;

	if (distribution.min() != pMin || distribution.max() != pMax)
		distribution = std::uniform_int_distribution<unsigned int>(pMin, pMax);

	return distribution(gen);
}