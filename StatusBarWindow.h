// StatusBarWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define STATUS_BAR_WINDOW_CLASS_NAME											STATUSCLASSNAME

#define STATUS_BAR_WINDOW_EXTENDED_STYLE										0
#define STATUS_BAR_WINDOW_TITLE													NULL
#define STATUS_BAR_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP )

BOOL StatusBarWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL StatusBarWindowGetRect( LPRECT lpRect );

BOOL StatusBarWindowSetText( LPCTSTR lpszStatusText );

LRESULT StatusBarWindowSize();
