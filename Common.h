// Common.h

#pragma once

#include <windows.h>

#define STRING_LENGTH															2048

#define ALL_FILES_FILTER														"*.*"
#define NEW_LINE_TEXT															"\r\n"

#define WINDOW_BORDER_WIDTH														::GetSystemMetrics( SM_CXBORDER )
#define WINDOW_BORDER_HEIGHT													::GetSystemMetrics( SM_CYBORDER )

#define SHELL_EXECUTE_OPEN_COMMAND												"open"
#define SHELL_EXECUTE_MINIMUM_SUCCESS_RETURN_VALUE								32
// Note that you need to cast ShellExecute to an INT_PTR in order to use the above, e.g.
//
//		// Open item
//		if( ( INT_PTR )ShellExecute( NULL, SHELL_EXECUTE_OPEN_COMMAND, lpszFilePath, NULL, NULL, SW_SHOWDEFAULT ) <= SHELL_EXECUTE_MINIMUM_SUCCESS_RETURN_VALUE )
//		{
//			// Unable to open item

#define UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING							"Unable to open '%s'"

#define ABOUT_MESSAGE_CAPTION													"About"
#define ERROR_MESSAGE_CAPTION													"Error"
#define INFORMATION_MESSAGE_CAPTION												"Information"
#define WARNING_MESSAGE_CAPTION													"Warning"
