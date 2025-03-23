// ListViewWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define LIST_VIEW_WINDOW_CLASS_NAME											WC_LISTVIEW

#define LIST_VIEW_WINDOW_EXTENDED_STYLE										LVS_EX_FULLROWSELECT
#define LIST_VIEW_WINDOW_TITLE												NULL
#define LIST_VIEW_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | LVS_REPORT )

#define LIST_VIEW_WINDOW_COLUMN_TITLES										{ "Name", "Modified" }

typedef enum
{
	LIST_VIEW_WINDOW_NAME_COLUMN_ID = 0,
	LIST_VIEW_WINDOW_MODIFIED_COLUMN_ID,

	LIST_VIEW_WINDOW_NUMBER_OF_COLUMNS

} LIST_VIEW_WINDOW_COLUMNS;

int ListViewWindowAddItem( LPCTSTR lpszItemText );

BOOL ListViewWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ListViewWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

BOOL ListViewWindowGetRect( LPRECT lpRect );

int ListViewWindowSetAllColumnWidths( int nColumnWidth = LVSCW_AUTOSIZE_USEHEADER );

HWND ListViewWindowSetFocus();
