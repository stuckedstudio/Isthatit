//Entrypoint for Game.


#include <SDL2/SDL.h>
#include "../Includes/main.hpp"
#include "../Includes/io.hpp"
#include <iostream>
#include <cstdlib>
int main()
{
    io* Io = new io();
    logger* Logger = new logger();
    const int dir_err = system("mkdir -p logs");
    if (-1 == dir_err)
    {
        Logger->log("Log dir already exists...");   
    }
    else
    {
        Logger->log("Created Log Dir");
    }
    
    Logger->log("Starting init...");
    return 0;
}
