#pragma once
#include <ctime>

#define LOG(x) std::cout << (x) << std::endl;

#define LOG_ER(x) std::cerr << "[ERROR] " << (x) << std::endl;

#define LOG_TIME_CHECK_S(x) unsigned int start = clock(); \
x; \
std::cout << "[TIME CHECK] " << #x << " :: " << (clock() - start) / 1000.0f << " s" << std::endl

#define LOG_TIME_CHECK_MS(x)  unsigned int start = clock(); \
x; \
std::cout << "[TIME CHECK] "  << #x << " :: " << (clock() - start) << " ms" << std::endl