// File.h

#pragma once

#include <windows.h>

#include "Resource.h"

#define MAIN_WINDOW_CLASS_NAME													"Main File Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_MAME												MAKEINTRESOURCE( IDR_MAIN_MENU )
#define MAIN_WINDOW_CLASS_SMALL_ICON											LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )

#define MAIN_WINDOW_EXTENDED_STYLE												WS_EX_CLIENTEDGE
#define MAIN_WINDOW_TITLE														"File"
#define MAIN_WINDOW_STYLE														WS_OVERLAPPEDWINDOW

#define MAIN_WINDOW_MINIMUM_WIDTH												500
#define MAIN_WINDOW_MINIMUM_HEIGHT												400

#define SYSTEM_MENU_SEPARATOR_ITEM_POSITION										5
#define SYSTEM_MENU_ABOUT_ITEM_POSITION											6
#define SYSTEM_MENU_ABOUT_ITEM_TEXT												"About"

#define ABOUT_MESSAGE_CAPTION													"About"
#define ERROR_MESSAGE_CAPTION													"Error"
#define INFORMATION_MESSAGE_CAPTION												"Information"
#define WARNING_MESSAGE_CAPTION													"Warning"

#define ABOUT_MESSAGE_TEXT														"Simple File Manager\r\n"						\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"March 2025"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to create main window"
#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to register main window class"
