#include "../Includes/io.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define DEBUG 1
std::vector<std::string> io::readCfg(std::string root)
{
    #ifdef DEBUG
    Logger->log("Accessing file: " + root + "/Assets/cfg.cfg");
    #endif
    std::ifstream cfgRead(root + "/Assets/cfg.cfg");
    std::vector<std::string> output = std::vector<std::string>();
    std::string buffer;
    if(cfgRead.fail())
    {
        Logger->log("Error in reading cfg.cfg");
        output.push_back("Error");
        return output;
    }
    else
    {
        Logger->log("Writing config file to buffer");
        buffer = std::string((std::istreambuf_iterator<char>(cfgRead)),
                 std::istreambuf_iterator<char>());
    }
    cfgRead.close();
    Logger->log("Config Read Complete : No errors to report, Thats good news !");
    while(buffer.find('\n') != std::string::npos)
    {
        int index;
        if(buffer.find('\n') != std::string::npos)
        {
        index = buffer.find('\n');
        output.push_back(std::string(buffer.substr(0,buffer.find('\n'))));
        buffer = buffer.replace(0,index+1,"");
        #ifdef DEBUG
        Logger->log("Remaining buffer : " + buffer);
        #endif
        }
        else
        {
            break;
        }
        
    }
    Logger->log("Returning config data");
    return output;
    
    
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
    std::ofstream logWrite(path.c_str(),std::fstream::app);
    logWrite << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logWrite << " ";
    #ifdef DEBUG
    std::cout << input << '\n';
    #endif
    logWrite << input << '\n';
    logWrite.close();
    
}
void logger::log(std::string input)
{    
    std::string path;
    path = logDir.c_str();
    path += "/";
    path += sessionName;
    path += ".log";
    std::ofstream logWrite(path.c_str(),std::fstream::app);
    logWrite << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logWrite << " ";
    #ifdef DEBUG
    std::cout << input << '\n';
    #endif
    logWrite << input << '\n';
    logWrite.close();
    
}