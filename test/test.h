/**
 * @file test.h
 * @author Techiesplash (techiesplash137@gmail.com)
 * @brief Small, platform-independent Unit Test tools for C++
 * @version 0.1
 * @date 2022-12-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TEST
#define TEST
#include <stdbool.h>

/**
 * @brief Names the unit test being done
 *
 * @param c Name of the test
 */
void tCase(char *c);

/**
 * @brief Asserts that this is true, and fails the test if it is not
 *
 * @param assertion The assertion. Expected to be a logical operation or similar
 * @param n The name of the assertion, this wll appear on the terminal
 * @return true The test passed
 * @return false The test failed
 */
bool tAssert(bool assertion, const char *n);

/**
 * @brief Print a message if the last test failed (non-formatted)
 *
 * @param message The message to print
 */
extern void tFailMsg(const char *message);

/**
 * @brief Print a message if the last test passed (non-formatted)
 *
 * @param message The message to print
 */
extern void tPassMsg(const char *message);

/**
 * @brief Dump specified data as hexidecimal if the last test failed
 *
 * @param title The name of the dump
 * @param data The data to dump
 * @param length The amount of data to dump
 */
void tFailDump(const char *title, void *data, int length);

/**
 * @brief Dump specified data as hexidecimal if the last test passed
 *
 * @param title The name of the dump
 * @param data The data to dump
 * @param length The amount of data to dump
 */
void tPassDump(const char *title, void *data, int length);
#ifdef __cplusplus

/**
 * @brief Print a message if the last test failed (formatted)
 *
 * @tparam Args Variadic argument typename
 * @param message The message to print (formatted)
 * @param args Arguments for that message
 */
template <typename... Args>
extern void tFailMsg(const char *message, Args... args);

/**
 * @brief Print a message if the last test passed (formatted)
 *
 * @tparam Args Variadic argument typename
 * @param message The message to print (formatted)
 * @param args Arguments for that message
 */
template <typename... Args>
extern void tPassMsg(const char *message, Args... args);

#include <vector>
/**
 * @brief Asserts there will be a specified exception in this function
 *
 * @tparam Ret The return type of the function
 * @tparam Ex The specified exception type
 * @tparam Args Variadic argument typename
 * @param function The function to test
 * @param n The name of the assertion, will show up in the terminal
 * @param args The arguments to give the function
 * @return true The test passed
 * @return false The test failed
 */
template <typename Ret, typename Ex, typename... Args>
bool tException(Ret (*function)(), const char *n, Args... args);

/**
 * @brief Asserts there will be no exception of any type in this function
 *
 * @tparam Ret The return type of the function
 * @tparam Args Variadic argument typename
 * @param function The function to test
 * @param n THe name of the assertion, will showup in the terminal
 * @param args The arguments to give the function
 * @return true The test passed
 * @return false The test failed
 */
template <typename Ret, typename... Args>
bool tNoException(Ret (*function)(), const char *n, Args... args);

class UnitField
{
public:
    char *name;
    UnitField(const char *name);
    virtual void Setup(){};
    virtual void Teardown(){};

    class UnitTest
    {
    public:
        char *name;
        void (*code)();

        UnitTest(const char *name, void (*code)());
    };

public:
    std::vector<UnitTest *> unitTests;
};

/**
 * @brief Runs the automatically-registered UnitField objects and the UnitTests within them
 *
 * @param abortOnFail Whether or not the program should exit with code 1 if a test fails
 */
void tRunTests(bool abortOnFail = true);
#endif
/**
 * @brief Finishes a unit test (Not to be used inside a UnitField)
 *
 */
bool tFinishTest();

/**
 * @brief Prints totals
 *
 */
bool tPrintTotalScore();

#include "test_impl.h"
#endif