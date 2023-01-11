/**
 * @file func.h
 * @author Techiesplash (techiesplash137@gmail.com)
 * @brief Declare some functions that can be used between multiple programs
 * @date 2022-12-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <vector>
/**
 * @brief Check if a file exists (from root dir)
 * 
 * @param file File to check
 * @return true File exists
 * @return false File does not exist
 */
extern bool FileExists(std::string file);


/**
 * @brief Refresh the list of programs to kill
 *
 */
extern std::vector<std::string> LoadKillList();


/**
 * @brief Writes a message to the daemon
 *
 * @param name File name to save to
 * @param token What to put in the file
 */
extern void WriteMessage(std::string name, std::string data = "");

/**
 * @brief Clear success/failure messages
 *
 */
extern void ClearSuccess();

/**
 * @brief Check if the daemon responded with a success or a failure
 * 
 * @return true Success
 * @return false Failure/No response
 */
extern bool CheckSuccess();

/**
 * @brief Attempt to activate the daemon
 *
 * @return true Activated successfully
 * @return false Failure to activate
 */
extern bool Activate();

/**
 * @brief Attempt to deactivate the daemon
 *
 * @return true Deactivated successfully
 * @return false Failure to deactivate
 */
extern bool Deactivate();

/**
 * @brief Create a File with the specified filename
 * 
 * @param filename The name and path of the file
 */
extern void CreateFile(std::string filename);