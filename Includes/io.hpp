#ifndef IO_H
#define IO_H
#include <iostream>
#include <vector>
class logger
{
    public:
        logger();
        ~logger(){};
        void log(const char* input);
        void log(std::string input);
    private:
        std::string logDir = "logs";
        std::string sessionName;
};
class io
{
    public:
    io(logger* l)
    {
        Logger = l;
    }
    ~io()
    {

    }
    std::vector<std::string> readCfg(std::string root);
    private:
    logger* Logger;
};
#endif