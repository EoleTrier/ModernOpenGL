#pragma once

#include <filesystem>
#include <fstream>


class Log
{
public:
	Log() {};
	~Log() {};

	void OpenFile(std::filesystem::path const& filename);
	void Print(const char* format, ...);
};