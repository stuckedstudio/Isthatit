#ifndef IO_H
#define IO_H
#include <iostream>
class io
{
    public:
    io()
    {

    }
    ~io()
    {

    }
    std::string readCfg();

};
class logger
{
    public:
        logger();
        ~logger(){};
        void log(const char* input);
    private:
        std::string logDir = "logs";
        std::string sessionName;
};
#endif