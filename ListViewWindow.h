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

#define LIST_VIEW_WINDOW_CURRENT_FOLDER_NAME								"."
#define LIST_VIEW_WINDOW_PARENT_FOLDER_NAME									".."

#define LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_FORMAT_STRING					"%c%s"
#define LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_PREFIX							ASCII_SPACE_CHARACTER

#define LIST_VIEW_WINDOW_MODIFIED_TEXT_FORMAT_STRING						"%04d/%02d/%02d %02d:%02d:%02d"

#define LIST_VIEW_WINDOW_POPULATING_STATUS_MESSAGE_FORMAT_STRING			"Populating %s ..."
#define LIST_VIEW_WINDOW_POPULATED_STATUS_MESSAGE_FORMAT_STRING				"%s (%d items)"
#define LIST_VIEW_WINDOW_UNABLE_TO_OPEN_FOLDER_STATUS_MESSAGE_FORMAT_STRING	"Unable to open folder %s"

typedef enum
{
	LIST_VIEW_WINDOW_NAME_COLUMN_ID = 0,
	LIST_VIEW_WINDOW_MODIFIED_COLUMN_ID,

	LIST_VIEW_WINDOW_NUMBER_OF_COLUMNS

} LIST_VIEW_WINDOW_COLUMNS;

int ListViewWindowAddItem( LPCTSTR lpszItemText );

BOOL ListViewWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ListViewWindowGetRect( LPRECT lpRect );

BOOL ListViewWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint = TRUE );

int ListViewWindowPopulate( LPCTSTR lpszFileFilter, BOOL( *lpStatusFunction )( LPCTSTR lpszStatusMessage ) );

int ListViewWindowPopulate( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter, BOOL( *lpStatusFunction )( LPCTSTR lpszStatusMessage ) );

int ListViewWindowSetAllColumnWidths( int nColumnWidth = LVSCW_AUTOSIZE_USEHEADER );

HWND ListViewWindowSetFocus();
