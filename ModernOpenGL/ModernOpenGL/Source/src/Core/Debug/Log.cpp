#include "Core/Debug/Log.h"
#include <iostream>
#include <cstdarg>

Log::~Log()
{
    m_File.close();
}

void Log::OpenFile(std::filesystem::path const& filename)
{
    m_File.open(filename, std::fstream::out);

    if (m_File.is_open())
    {
        std::cout << "Open file: " << filename << std::endl;
    }
    else 
        std::cout << "Cannot open the file: " << filename << std::endl;
}

void Log::Print(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
        
    vsprintf_s(buffer, sizeof(buffer), format, args);
    std::cout << buffer << std::endl;

    if (m_File.is_open())
    {
        m_File << buffer << std::endl;
        m_File.flush();
    }
    va_end(args);
}
