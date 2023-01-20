/**
 * @file dummy.cpp
 * @author Techiesplash (techiesplash137@domain.com)
 * @brief Dummy program for the test
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <thread>
#include <chrono>
#include <cstdio>

int main()
{
    while (true)
    {
        FILE *fp = fopen("./foo.msg", "r");
        if (fp)
        {
            fclose(fp);
            fp = fopen("./bar.msg", "w");
            if (fp)
            {
                fclose(fp);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}