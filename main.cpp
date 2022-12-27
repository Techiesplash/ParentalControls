/**
 * @file main.cpp
 * @author techiesplash (techiesplash137@gmail.com)
 * @brief This program is meant to enforce parental controls on a 10-year-old who does not know the root password. It is not designed very securely.
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#define HASH_PASS false
#define DEFAULT_ACTIVE true
#define USE_ONLY_BUILTIN_LIST false
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>
#include <string.h>

using namespace std;

vector<string> programs = {};

bool active = DEFAULT_ACTIVE;

/**
 * @brief Check if a file exists ("from root dir") and respond
 * 
 * @param filename The name of the file
 * @return true File exists
 * @return false File does not exist
 */
bool CheckForFile(string filename)
{

    FILE *fp = fopen(string("/" + filename).c_str(), "r");
    if (fp != NULL)
    {
        remove(string(string("/") + "failure.msg").c_str());
        remove(string(string("/") + "success.msg").c_str());
        char buf[64];
        if (fgets(buf, sizeof(buf), fp) != NULL)
        {

            fclose(fp);
            remove(string(string("/") + filename).c_str());

            FILE *fr = fopen(string(string("/") + "success.msg").c_str(), "w");
            fclose(fr);
            return true;
        }
        fclose(fp);
        remove(string(string("/") + filename).c_str());
    }
    return false;
}
/**
 * @brief Refresh the list of programs to kill 
 * 
 */
void RefreshKillList()
{
    if (!USE_ONLY_BUILTIN_LIST)
    {
        FILE *fp = fopen(string(string("/") + "pc.list").c_str(), "r");
        if (fp != NULL)
        {
            static char *line;
            static size_t len;
            static ssize_t read;

            programs.clear();

            while ((read = getline(&line, &len, fp)) != -1)
            {
                if(line != "")
                {
                    programs.push_back(string(line));
                }
            }

            fclose(fp);

            return;
        }
    }
}

/**
 * @brief Check if a file exists (from root dir)
 * 
 * @param file File to check
 * @return true File exists
 * @return false File does not exist
 */
bool FileExists(string file)
{
    FILE *fp = fopen(string(string("/") + file).c_str(), "r");
    if (fp)
    {
        fclose(fp);
        return true;
    }
    return false;
}

bool Criteria()
{
    if (CheckForFile("activate.msg"))
    {
        active = true;
    }
    if (CheckForFile("deactivate.msg"))
    {
        active = false;
    }
    if (!USE_ONLY_BUILTIN_LIST)
    {
        if (FileExists("refresh.msg"))
        {
            remove(string(string("/") + "refresh.msg").c_str());
            RefreshKillList();
            FILE *fp = fopen(string(string("/") + "success.msg").c_str(), "w");
            if (fp)
            {
                fclose(fp);
            }
        }
    }
    return active;
}

/**
 * @brief Kills the programs in the list
 * 
 */
void KillProgramsTick()
{
    for (auto p : programs)
    {
        system(string("killall " + p).c_str());
    }
}

int main()
{
    // Root check
    FILE* fp = fopen("/roottest", "w");
    if(fp)
    {
        fclose(fp);
        remove("/roottest");
    }
    else
    {
        puts("Failed to start: Needs root permissions");
        exit(1);
    }

    if (FileExists("pc.startdisabled"))
    {
        active = false;
    }



    // Setup
    remove(string(string("/") + "activate.token").c_str());
    remove(string(string("/") + "deactivate.token").c_str());
    remove(string(string("/") + "failure.msg").c_str());
    remove(string(string("/") + "success.msg").c_str());
    remove(string(string("/") + "refresh.msg").c_str());

    if (!USE_ONLY_BUILTIN_LIST)
    {
        RefreshKillList();
    }

    // Main Loop
    while (true)
    {
        if (Criteria())
        {
            KillProgramsTick();
             printf("on\n");
        }
        else
        {
             printf("off\n");
        }
        this_thread::sleep_for(chrono::milliseconds(750));
    }
    return 0;
}
