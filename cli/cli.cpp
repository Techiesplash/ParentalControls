/**
 * @file cli.cpp
 * @author Techiesplash (techiesplash137@gmail.com)
 * @brief Command Line Interface (CLI) program to interface with the Parental Controls
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <string.h>
#include "../reusable/reusable.h"

using namespace std;

// Message that gets printed for help, of course
string help = R"HELP(

Parental Controls CLI - Help
About:
    This is a simple, minimalist system intended
    to enforce parental controls upon those without
    root access.

    This quickly terminates any program found within a list.

    MIT Licensed, by Techiesplash (2022)
    https://github.com/Techiesplash/ParentalControls

Usage:
    parentalctl disable/enable - Toggle whether the daemon should start activated
    parentalctl start/stop - Toggle whether or not the daemon will currently enforce
    parentalctl show - Display the list of programs to kill
    parentalctl add [program]... - Add program(s) to the list (path or name)
    parentalctl remove [program]... - Remove the following program(s) from the list

)HELP";

// List of programs to kill
vector<string> killList;

// Save the list to a file so the daemon can read it
void SaveKillList()
{
    remove("/pc.list");
    FILE *fp = fopen("/pc.list", "w");
    if (fp != NULL)
    {

        for (int i = 0; i < (int)killList.size(); i++)
        {
            fputs(string(killList[i]).c_str(), fp);
        }

        fclose(fp);

        fp = fopen("/refresh.msg", "w");
        if (fp)
        {
            fclose(fp);
        }
    }
}

// Start here
int main(int argc, char **argv)
{
    // Check for root permissions
    FILE *fp = fopen("/roottest", "w");
    if (fp)
    {
        fclose(fp);
        remove("/roottest");
    }
    else
    {
        cout << "Requires root permissions. Try running with \"sudo\"?" << endl;
        exit(0);
    }

    // Load the kill list
    killList = LoadKillList();

    // Use the arguments
    if (argc >= 2)
    {
        // ==========================================================HELP
        if (strcmp(argv[1], "help") == 0)
        {
            cout << help << endl;
        }
        // ==========================================================DISABLE
        else if (strcmp(argv[1], "disable") == 0)
        {
            fp = fopen("/pc.startdisabled", "w");
            if (FileExists("/pc.startdisabled"))
            {
                fclose(fp);
            }
            else
            {
                cout << "Failed to execute action" << endl;
            }
        }
        // ==========================================================ENABLE
        else if (strcmp(argv[1], "enable") == 0)
        {
            remove("/pc.startdisabled");
            if (FileExists("/pc.startdisabled"))
            {
                cout << "Failed to execute action" << endl;
            }
        }
        // ==========================================================START
        else if (strcmp(argv[1], "start") == 0)
        {

            if (Activate())
            {
                remove("/success.msg");
            }
            else
            {
                remove("/activate.msg");
                remove("/failure.msg");
                cout << "Failed to execute action" << endl;
            }
        }
        // ==========================================================STOP
        else if (strcmp(argv[1], "stop") == 0)
        {
            if (Deactivate())
            {
                remove("/success.msg");
            }
            else
            {
                remove("/activate.msg");
                remove("/failure.msg");
                cout << "Failed to execute action" << endl;
            }
        }
        // ==========================================================SHOW
        else if (strcmp(argv[1], "show") == 0)
        {
            if (killList.size() == 0)
            {
                cout << "No programs to kill" << endl;
            }
            else
            {
                for (int i = 0; i < (int)killList.size(); i++)
                {
                    cout << killList[i];
                }
            }
        }
        // ==========================================================REMOVE
        else if (strcmp(argv[1], "remove") == 0)
        {
            for (int i = 0; i < (int)killList.size(); i++)
            {
                for (int j = 2; j < argc; j++)
                {
                    if (killList[i] == string(argv[j]) + string("\n"))
                    {
                        killList.erase(killList.begin() + i);
                    }
                }
            }
            SaveKillList();
        }
        // ==========================================================ADD
        else if (strcmp(argv[1], "add") == 0)
        {
            for (int i = 2; i < argc; i++)
            {
                bool available = true;
                for (int j = 0; j < (int)killList.size(); j++)
                {
                    if (killList[j] == string(argv[i]))
                    {
                        available = false;
                    }
                }
                if (available)
                {
                    killList.push_back(string(string(argv[i]) + "\n"));
                }
            }
            SaveKillList();
        }
        // ==========================================================UNKNOWN
        else
        {
            cout << "Unknown command \"" + string(argv[1]) + "\": Type \"parentalctl help\" for help." << endl;
        }
    }
    else
    {
        // No arguments. Assume the user does not know how to use thiss
        cout << help << endl;
    }
}