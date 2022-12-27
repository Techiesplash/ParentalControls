#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <string.h>

using namespace std;

string help = R"HELP(

Parental Controls CLI - Help
About:
    This is a simple, minimalist system intended
    to enforce parental controls upon those without
    root access.

    This quickly terminates any program found within a list.

    MIT Licensed, by Techiesplash (2022)

Usage:
    parentalctl disable/enable - Toggle whether the daemon should start activated
    parentalctl start/stop - Toggle whether or not the daemon will currently enforce
    parentalctl show - Display the list of programs to kill
    parentalctl add [program]... - Add program(s) to the list (path or name)
    parentalctl remove [program]... - Remove the following program(s) from the list
)HELP";

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

std::vector<string> killList;

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

void RefreshKillList()
{

    FILE *fp = fopen(string("/pc.list").c_str(), "r");
    if (fp != NULL)
    {
        static char *line;
        static size_t len;
        static ssize_t read;

        killList.clear();

        while ((read = getline(&line, &len, fp)) != -1)
        {
            killList.push_back(string(line));
        }

        fclose(fp);

        return;
    }
}

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

    RefreshKillList();

    if (argc >= 2)
    {
        if (strcmp(argv[1], "help") == 0)
        {
            cout << help << endl;
        }
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
        else if (strcmp(argv[1], "enable") == 0)
        {
            remove("/pc.startdisabled");
            if (FileExists("pc.startdisabled"))
            {
                cout << "Failed to execute action" << endl;
            }
        }
        else if (strcmp(argv[1], "start") == 0)
        {

            fp = fopen("/activate.msg", "w");
            if (fp)
            {
                fclose(fp);
            }
            this_thread::sleep_for(chrono::milliseconds(750));
            if (FileExists("success.msg"))
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
        else if (strcmp(argv[1], "stop") == 0)
        {

            fp = fopen("/deactivate.msg", "w");
            if (fp)
            {
                fclose(fp);
            }
            this_thread::sleep_for(chrono::milliseconds(750));
            if (FileExists("success.msg"))
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
        else
        {
            cout << "Unknown command \"" + string(argv[1]) + "\": Type \"parentalctl help\" for help." << endl;
        }
    }
    else
    {
        cout << help << endl;
    }
}