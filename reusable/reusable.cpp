/**
 * @file func.cpp
 * @author Techiesplash (techiesplash137@gmail.com)
 * @brief Defines some functions that can be shared between multiple programs
 * @version 0.1
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "reusable.h"
#include <thread>
#include <chrono>


void WriteMessage(std::string name, std::string data)
{
    remove(std::string(name + ".msg").c_str());
    puts(std::string(name + ".msg\n").c_str());
    FILE *fp = fopen(std::string(name + ".msg").c_str(), "w");
    if (fp != NULL)
    {
        fprintf(fp, data.c_str());

        fclose(fp);
    }
    else
    {
        printf("Failed to open file for writing!\n");
    }
}

void ClearSuccess()
{
    remove("/success.msg");
    remove("/failure.msg");
}

bool CheckSuccess()
{
    FILE *fp = fopen("/success.msg", "r");
    if (fp != NULL)
    {
        fclose(fp);
        return true;
    }
    fp = fopen("/failure.msg", "r");
    if (fp != NULL)
    {
        fclose(fp);
        return false;
    }
    puts("Did not see any SUCCESS or FAILURE messages: Check daemon?");
    return false;
}

bool Activate()
{
    ClearSuccess();
    WriteMessage("/activate");
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    return CheckSuccess();
}

bool Deactivate()
{
    ClearSuccess();
    WriteMessage("/deactivate");
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    return CheckSuccess();
}

bool FileExists(std::string file)
{
    FILE *fp = fopen(file.c_str(), "r");
    if (fp)
    {
        fclose(fp);
        return true;
    }
    return false;
}

std::vector<std::string> LoadKillList()
{
    std::vector<std::string> vec;

    FILE *fp = fopen("/pc.list", "r");
    if (fp != NULL)
    {
        static char *line;
        static size_t len;
        static ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (line != "")
            {
                vec.push_back(std::string(line));
            }
        }

        fclose(fp);
    }

    return vec;
}

void CreateFile(std::string filename)
{
    FILE* fp = fopen(filename.c_str(), "w");
    if(fp != NULL)
    {
        fclose(fp);
    }
}