#include "func.h"

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