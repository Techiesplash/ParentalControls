#pragma once
#include <string>

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