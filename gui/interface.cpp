#include "interface.h"
#include <chrono>
#include <thread>

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