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

#define DEFAULT_ACTIVE true
#define USE_ONLY_BUILTIN_LIST false

#include <filesystem>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>
#include <string.h>
#include "../reusable/reusable.h"

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
    if (FileExists(filename))
    {

        remove(filename.c_str());

        CreateFile("/success.msg");
        return true;
    }
    // If the file could not be opened
    return false;
}

/**
 * @brief
 *
 * @return true The program can kill programs
 * @return false The program cannot kill programs
 */
bool Criteria()
{
    if (CheckForFile("/activate.msg"))
    {
        // Activate message received
        active = true;
    }
    if (CheckForFile("/deactivate.msg"))
    {
        // Deactivate message received
        active = false;
    }
    if (CheckForFile("/requeststatus.msg"))
    {
        // Interface requests current status
        if (active)
        {
            FILE *fp = fopen("/statuson.msg", "w");
            if (fp)
            {
                fclose(fp);
            }
        }
        else
        {
            FILE *fp = fopen("/statusoff.msg", "w");
            if (fp)
            {
                fclose(fp);
            }
        }
        remove("/requeststatus.msg");
    }
    if (!USE_ONLY_BUILTIN_LIST)
    {
        // Refresh the list
        if (FileExists("/refresh.msg"))
        {
            // Refresh message received
            remove("/refresh.msg");
            programs = LoadKillList();
            FILE *fp = fopen("/success.msg", "w");
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
    // Cycle through all the programs and kill all of them
    for (auto p : programs)
    {
        system(string("killall " + p).c_str());
    }
}

int main()
{
    // Check if it is being run as root
    FILE *fp = fopen("/roottest", "w");
    if (fp)
    {
        // Has root perms
        fclose(fp);
        remove("/roottest");
    }
    else
    {
        // Needs root perms
        puts("Failed to start: Needs root permissions");
        exit(1);
    }

    // Check if it should start disabled
    if (FileExists("/pc.startdisabled"))
    {
        active = false;
    }

    // Setup / Cleanup
    remove("/activate.token");
    remove("/deactivate.token");
    remove("/failure.msg");
    remove("/success.msg");
    remove("/refresh.msg");

    // Reload the kill list on load
    if (!USE_ONLY_BUILTIN_LIST)
    {
        programs = LoadKillList();
    }

    // Main Loop
    while (true)
    {
        if (Criteria())
        {
            KillProgramsTick();
        }
        // Wait for 0.75 seconds every tick
        this_thread::sleep_for(chrono::milliseconds(750));
    }
    return 0;
}
