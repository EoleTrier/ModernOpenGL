#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdarg>


class Log
{
public:
	Log() {};
	~Log();

	void OpenFile(std::filesystem::path const& filename);
	void Print(const char* format, ...);

private:
	std::fstream m_File;
};