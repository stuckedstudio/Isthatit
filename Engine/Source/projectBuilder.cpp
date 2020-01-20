//Created because I didn't want to learn to make make files... Sorry
#include <iostream>
#include <unistd.h>
#include <filesystem>
//Defining our search area for cpp files
std::string root;
std::string source;
namespace fs = std::filesystem;
int main(int argc, char** argv)
{
    std::string extraCommands = "";
    std::string extraEndCommands = "";
    int clean = 1;
    for(int i = 1; i < argc;i++)
    {   
        if(std::string(argv[i]) == "--no-clean")
        {
                clean = 0;     
        }
        else if(std::string(argv[i]).find("--end-args=") != std::string::npos)
        {
            extraEndCommands += std::string(argv[i]).substr(std::string(argv[i]).find("=")+1,std::string(argv[i]).size()-(std::string(argv[i]).find("=")+1));
            extraEndCommands += " ";
        }
        
        else
        {
            extraCommands += argv[i];
            extraCommands += " ";
        }
        
       
    }
    std::cout << "Extra Commands: " << extraCommands << std::endl;
    //Getting the current directory and our Source directory
    root = fs::current_path();
    std::cout << "Root set as: " << root << std::endl;
    source = root + "/Source";
    std::string bin, userbin; /*TEMPORARY!!*/userbin = "/Bin";
    bin = root + userbin;
    bool binExist;
    //Compiling all cpp files...
    for (const auto & entry : fs::directory_iterator(source))
    {
        std::string command = "g++ -std=c++17 -c " + extraCommands + " " + entry.path().generic_string() + " " + extraEndCommands;
        std::cout << "Executing : " << command << std::endl;
        system(command.c_str());
    }
    //Preparing for the final compile
    std::string compileCommand = "g++ -std=c++17 ";
    compileCommand += extraCommands;
    compileCommand += "-o ";
    compileCommand += bin;
    compileCommand += "/exec.o ";
    for (const auto & entry : fs::directory_iterator(root))
    {
        //Check if the Bin folder exists.
        if(entry.path().generic_string().find(userbin) != std::string::npos)
        {
            binExist = true;
        }
        //Making sure that we are not trying to implement our project builder into the final release
        if(entry.path().generic_string().find("build.o") == std::string::npos && entry.path().generic_string().find("projectBuilder") == std::string::npos)
        {
            //Making sure that we are not adding other junk files in the directory into the compiling process
            if(entry.path().generic_string().find(".o") != std::string::npos)
            {
                //Removing the rest of the path, that we don't need.
                int tmpIndex = entry.path().generic_string().find_last_of('/');
                tmpIndex++;
                std::string tmp = entry.path().generic_string().substr(tmpIndex,entry.path().generic_string().size()-tmpIndex);
                //Verbose feature to see what we picked up, in case it does something wrong, it will be easier to find out what happened.
                std::cout << "Found File: " << tmp << std::endl;
                tmp += " ";
                //Finalizing the build command
                compileCommand += tmp;
            }
        }
    }
    //Creates bin if not exist
    if(!binExist)
    {
        fs::create_directory(bin);
    }
    //Adding end-args (Due to the fact that g++ cares about argument placement...)
    compileCommand += extraEndCommands;
    //Showing the build command to make sure that we got the command we needed
    std::cout << "Full compile command: " << compileCommand << std::endl;
    //Running the build.
    system(compileCommand.c_str());
    //Checking if we asked the program to cleanup (Default enabled: Can be turned off with a -no-clean argument)
    if(clean == 1)
    {
        std::cout << "Cleaning up..." << std::endl;
        std::string removeCommand = "rm ";
        for (const auto & entry : fs::directory_iterator(root))
        {
            //Checks to make sure that we are not in the middle of deleting the Builder program.
            if(entry.path().generic_string().find(".o") != std::string::npos && entry.path().generic_string().find("build.o") == std::string::npos)
            {
                //Removing the rest of the path, that we don't need.
                int tmpIndex = entry.path().generic_string().find_last_of('/');
                tmpIndex++;
                std::string tmp = entry.path().generic_string().substr(tmpIndex,entry.path().generic_string().size()-tmpIndex);
                //Verbose feature to see what we picked up, in case it does something wrong, it will be easier to find out what happened.
                std::cout << "File : " << tmp << " Marked for removal."<< std::endl;
                tmp += " ";
                removeCommand += tmp;
            }
        }
        system(removeCommand.c_str());
    }
    std::cout << "Excecutable can be found at: " << bin << "/exec.o" << std::endl;
    return 0;
}