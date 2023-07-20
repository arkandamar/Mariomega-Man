#pragma once

#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <math.h>

namespace utils {
	int extractValue(const std::string& s, const std::string& del)
	{
		size_t del_pos = s.find(del);
		return stoi(s.substr(del_pos + del.size(), s.size() - del_pos));
	}

	std::string extractValueStr(const std::string& s, const std::string& del)
	{
		size_t del_pos = s.find(del);
		return s.substr(del_pos + del.size(), s.size() - del_pos);
	}

	float rad(float deg)
	{
		return  deg * (float)(M_PI / 180);
	}

	float mapping(float output_start, float output_end, float input_start, float input_end, float input)
	{
		return output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
	}
}