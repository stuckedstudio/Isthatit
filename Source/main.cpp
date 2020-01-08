//Entrypoint for Game.

#define np std::string::npos
#include <SDL2/SDL.h>
#include "../Includes/main.hpp"
#include "../Includes/io.hpp"
#include <iostream>
#include <filesystem>
#include <vector>
#ifndef DEBUG
#define DEBUG 1
#endif
namespace fs = std::filesystem;
bool isRunning = false;
bool Errored = false;
logger* Logger;
io* Io;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Event Event;
void Render()
{
    SDL_RenderClear(renderer);
    //Add graphics here
    SDL_SetRenderDrawColor(renderer,0,255,0,1);
    SDL_RenderPresent(renderer);

}
void clean()
{
    Logger->log("Cleaning up :)");
    SDL_Quit();
}
void EventHandle()
{
    while(SDL_PollEvent(&Event) != 0)
    {
        if(Event.type == SDL_WINDOWEVENT)
        {
            switch(Event.window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                isRunning = false;
            break;
            default:
            break;
        }
        }
    }
}
struct sysConf
{
    int sizeX,sizeY;
    bool fullscreen;

};
struct sysConf configParse(std::vector<std::string> cfgInput)
{
    struct sysConf currConf;
    //To make sure that no values are NULL, we set them to 0
    currConf.fullscreen = 0;
    currConf.sizeX = 0;
    currConf.sizeY = 0;
        #ifdef DEBUG
        #if DEBUG == 1
            for(int c = 0; c < cfgInput.size();c++)
            {
                Logger->log(std::string("cfg vector at ") + std::to_string(c) + std::string(" Contains: ") + cfgInput.at(c));
            }
        #endif
        #endif
    for(int i = 0; i < cfgInput.size();i++)
    {
        if(cfgInput.at(i) == std::string("Error"))
        {
            Errored = true;
            return currConf;
        }
        else
        {
            if(cfgInput.at(i).find("width=") != np)
            {
                currConf.sizeX = std::stoi(cfgInput.at(i).substr(cfgInput.at(i).find_first_of('"')+1,cfgInput.at(i).size()-cfgInput.at(i).find_first_of('"')-1));
            }
            else if(cfgInput.at(i).find("height=") != np)
            {
                currConf.sizeY = std::stoi(cfgInput.at(i).substr(cfgInput.at(i).find_first_of('"')+1,cfgInput.at(i).size()-cfgInput.at(i).find_first_of('"')-1));
            }
            else if(cfgInput.at(i).find("fullscreen=") != np)
            {
                currConf.fullscreen = std::stoi(cfgInput.at(i).substr(cfgInput.at(i).find_first_of('"')+1,cfgInput.at(i).size()-cfgInput.at(i).find_first_of('"')-1));
            }
            else
            {
                Logger->log("An unknown option in the config is detected : Attempts to ignore...");
            }
            
        }
        
    }
    return currConf;
}
int main()
{
    struct sysConf currentSysConfig;
    Logger = new logger();
    Io = new io(Logger);
    std::string gameRoot = fs::current_path();
    
    bool logDirExist = false;
    for (const auto & entry : fs::directory_iterator(gameRoot))
    {
        if(entry.path().generic_string().find("logs") != np)
        {
            logDirExist = true;
        }
    }
    if(logDirExist)
    {
        Logger->log("logs dir exists");
        Logger->log("Root defined as " + gameRoot);
    }
    else
    {
        fs::create_directory("logs");
        Logger->log("Created log dir");
        Logger->log("Root defined as " + gameRoot);
    }
    Logger->log("Starting init... So far so good :)");
    Logger->log("Reading config...");
    currentSysConfig = configParse(Io->readCfg(gameRoot));
    if(Errored)
    {
        Logger->log("Config Could not be read... Not recoverable - Dying");
        return 33;
    }
    else
    {
        Logger->log("Config read - No errors to report");
        Logger->log("Current config is: "+std::to_string(currentSysConfig.sizeY)+"px"+'\n'+std::to_string(currentSysConfig.sizeX)+"px"+'\n'+"fullscreen:"+std::to_string(currentSysConfig.fullscreen)+'\n');
    }
    
    Uint32 flags;
    switch(int(currentSysConfig.fullscreen))
    {
        case 0:
            flags = 0;
            break;
        case 1:
            flags = SDL_WINDOW_BORDERLESS;
            break;
        default:
            Logger->log("An uknown value was detected, while trying to set fullscreen status - defaulting to windowed.");
            flags = 0;
            break;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        Logger->log("SDL error - INIT_EVERYTHING failed... SDL ERROR : " + std::string(SDL_GetError()));
        return 33; 
    }
    if(SDL_CreateWindowAndRenderer(
        currentSysConfig.sizeX,
        currentSysConfig.sizeY,
        flags|SDL_WINDOW_SHOWN,
        &window,
        &renderer
        ))
        {
            Logger->log("SDL error - Window or Renderer could not be created... SDL ERROR : " + std::string(SDL_GetError()));
            return 33;
        }
        else
        {
            //We can now let the main loop run :)
            isRunning = true;
        }
        while(isRunning)
        {
            Render();
            EventHandle();
        }
        clean();
        
    return 0;
}