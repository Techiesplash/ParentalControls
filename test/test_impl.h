/**
 * @file test_impl.h
 * @author Techiesplash (techiesplash137@gmain.com)
 * @brief Definitions for tester
 * @version 0.1
 * @date 2022-12-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

bool exitOnFail = false;
bool lastTestFailed = false;
int failuresInTest = 0;
int successesInTest = 0;
int totalFails = 0;
int totalPass = 0;
int testCount = 0;
char *testname = "";

#ifdef __cplusplus
#include <iostream>
#include <exception>
UnitField *initializingField;
#endif

void tCase(char *c)
{
    testname = c;
}

bool tAssert(bool assertion, const char *n)
{
    if (assertion)
    {
        printf("\e[1;32m\nAssertion \"%s\" passed\e[0m\n", n);
        lastTestFailed = false;
        successesInTest++;
        return true;
    }
    else
    {
        printf("\e[1;31m\nAssertion \"%s\" failed\n\e[0m", n);
        lastTestFailed = true;
        failuresInTest++;
        return false;
    }
}

#ifdef __cplusplus
template <typename Ret, typename Ex, typename... Args>
bool tException(Ret (*function)(), const char *n, Args... args)
{
    try
    {
        function(args...);
    }
    catch (const Ex &e)
    {
        printf("\e[1;32m\nException \"%s\" passed: Exception=%s\e[0m\n", n, e.what());
        successesInTest++;
        lastTestFailed = false;
        return true;
    }
    catch (const std::exception &e)
    {
        printf("\e[1;31mException \"%s\" failed: Exception=%s\e[0m\n", n, e.what());
        failuresInTest++;
        lastTestFailed = true;
        return false;
    }
    printf("\e[1;31mException \"%s\" failed: Exception=None\e[0m\n", n);
    failuresInTest++;
    lastTestFailed = true;
    return false;
}

template <typename Ret, typename... Args>
bool tNoException(Ret (*function)(), const char *n, Args... args)
{
    try
    {
        function(args...);
    }
    catch (const std::exception &e)
    {
        printf("\e[1;31mNoException \"%s\" failed: Exception=%s\e[0m\n", n, e.what());
        failuresInTest++;
        lastTestFailed = true;
        return false;
    }
    printf("\e[1;32m\nNoException \"%s\" passed\e[0m\n", n);
    successesInTest++;
    lastTestFailed = false;
    return true;
}

template <typename... Args>
void tFailMsg(const char *message, Args... args)
{
    if (lastTestFailed)
    {
        printf(message, args...);
    }
}
template <typename... Args>
void tPassMsg(const char *message, Args... args)
{
    if (!lastTestFailed)
    {
        printf(message, args...);
    }
}
#endif

void tFailMsg(const char *message)
{
    if (lastTestFailed)
    {
        puts("\e[0;33m");
        printf(message);
        puts("\e[0m");
    }
}

void tPassMsg(const char *message)
{
    if (!lastTestFailed)
    {
        puts("\e[0;36m");
        printf(message);
        puts("\e[0m");
    }
}

void Dump(const char *title, void *data, int length)
{

    printf("\nDump \"%s\" ============\n\e[0;35m", title);
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < length; ++i)
    {
        printf("%02X ", ((unsigned char *)data)[i]);
        if (((unsigned char *)data)[i] >= ' ' && ((unsigned char *)data)[i] <= '~')
        {
            ascii[i % 16] = ((unsigned char *)data)[i];
        }
        else
        {
            ascii[i % 16] = '.';
        }
        if ((i + 1) % 8 == 0 || i + 1 == length)
        {
            printf(" ");
            if ((i + 1) % 16 == 0)
            {
                printf("|  %s \n", ascii);
            }
            else if (i + 1 == length)
            {
                ascii[(i + 1) % 16] = '\0';
                if ((i + 1) % 16 <= 8)
                {
                    printf(" ");
                }
                for (j = (i + 1) % 16; j < 16; ++j)
                {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
    puts("\e[0m");
}

void tFailDump(const char *title, void *data, int length)
{
    if (lastTestFailed)
    {
        Dump(title, data, length);
    }
}

void tPassDump(const char *title, void *data, int length)
{
    if (!lastTestFailed)
    {
        Dump(title, data, length);
    }
}
#ifdef __cplusplus
std::vector<UnitField *> unitFields;

UnitField::UnitField(const char *name)
{
    initializingField = this;
    this->name = (char *)name;
    unitFields.push_back(this);
}
UnitField::UnitTest::UnitTest(const char *name, void (*code)())
{
    this->name = (char *)name;
    this->code = code;
    initializingField->unitTests.push_back(this);
}

void tRunTests(bool abortOnFail)
{

    puts("Beginning Unit Tests...");
    for (int i = 0; i < (int)unitFields.size(); i++)
    {
        unitFields[i]->Setup();
        for (int j = 0; j < (int)unitFields[i]->unitTests.size(); j++)
        {
            // Run tests
            unitFields[i]->unitTests[j]->code();

            // Print results
            printf("\nTest #%i \"%s\" Results: \e[1;32m%i\e[0m tests passed, \e[1;31m%i\e[0m failed.\n", testCount++, unitFields[i]->unitTests[j]->name, successesInTest, failuresInTest);

            if (failuresInTest > 0)
            {
                puts("One or more tests failed, exiting...");
                exit(1);
            }

            totalFails += failuresInTest;
            totalPass += successesInTest;
            failuresInTest = 0;
            successesInTest = 0;
            lastTestFailed = false;
        }
        unitFields[i]->Teardown();
    }

    printf("\nFinished Unit Tests. \e[1;32m%i\e[0m tests passed, \e[1;31m%i\e[0m failed.\n", totalPass, totalFails);
}
#endif

bool tPrintTotalScore()
{
    printf("\nTotal Unit Test Score: \e[1;32m%i\e[0m tests passed, \e[1;31m%i\e[0m failed.\n", totalPass, totalFails);
    return totalFails == 0;
}

bool tFinishTest()
{
    // Print results
    printf("\nTest %i \"%s\" Results: \e[1;32m%i\e[0m tests passed, \e[1;31m%i\e[0m failed.\n", testCount++, testname, successesInTest, failuresInTest);

    totalFails += failuresInTest;
    totalPass += successesInTest;
    failuresInTest = 0;
    successesInTest = 0;
    lastTestFailed = false;
    testname = "";
    return failuresInTest == 0;
}
