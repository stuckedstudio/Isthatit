#include "../Includes/io.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <cstdlib>
std::string io::readCfg()
{
    std::ifstream cfgRead("Assets/cfg.cfg",std::ifstream::in);
    if(cfgRead.fail())
    {
        return "Error";
    }
    else
    {
        std::string result((std::istreambuf_iterator<char>(cfgRead)),
                 std::istreambuf_iterator<char>());
        cfgRead.close();
        return result;
    }
    return "error";
    
    
}
logger::logger()
{
    auto start = std::chrono::system_clock::now();
    std::time_t currTime = std::chrono::system_clock::to_time_t(start);
    std::stringstream ss;
    ss << currTime;
    sessionName = ss.str();
    
}
void logger::log(const char* input)
{    
    std::string path;
    path = logDir.c_str();
    path += "/";
    path += sessionName;
    path += ".log";
    std::ofstream logWrite(path.c_str());
    logWrite << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logWrite << " ";
    logWrite << input << '\n';
    logWrite.close();
    
}