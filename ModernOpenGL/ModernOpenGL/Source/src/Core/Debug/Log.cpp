#include "Core/Debug/Log.h"

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
    va_list args;
    va_start(args, format);
        
    while (*format != '\0')
    {
        if (*format != '%')
        {
            if (m_File.is_open())
                m_File.write(format, 1);
            std::cout << *format;
            format++;
            continue;
        }
        if (*(format + 1) != 'd' && *(format + 1) != 'i' && *(format + 1) != 'c' && *(format + 1) != 'f')
        {

            if (m_File.is_open())
                m_File.write(format, 1);
            std::cout << *format;
          
        }
        format++;

        switch (*format)
        {
            case ('i'):
            {
                int i = va_arg(args, int);
                std::cout << i;
                if (m_File.is_open())
                {
                    std::string str = std::to_string(i);
                    m_File.write(str.c_str(), str.size());
                }
                break;
            }
            case ('d'):
            {
                int i = va_arg(args, int);
                std::cout << i;
                if (m_File.is_open())
                {
                    std::string str = std::to_string(i);
                    m_File.write(str.c_str(), str.size());
                }
                break;
            }
            case ('c'):
            {
                int c = va_arg(args, int);
                std::cout << static_cast<char>(c);
                if (m_File.is_open())
                {
                    std::string str = std::to_string(static_cast<char>(c));
                    m_File.write(str.c_str(), str.size());
                }
                break;
            }
            case ('f'):
            {
                double d = va_arg(args, double);
                std::cout << d;
                if (m_File.is_open())
                {
                    std::string str = std::to_string(d);
                    m_File.write(str.c_str(), str.size());
                }
                break;
            }
            default:
            {

                if (m_File.is_open())
                    m_File.write(format, 1);
                std::cout << *format;
                break;
            }
        }
        ++format;
    }
    m_File.flush();
    va_end(args);
}
