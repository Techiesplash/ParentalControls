/**
 * @file func.h
 * @author Techiesplash (techiesplash137@gmail.com)
 * @brief Header for some reusable functions
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