// ListViewWindow.cpp

#include "ListViewWindow.h"

// Global variables
static HWND g_hWndListView;

int ListViewWindowAddItem( LPCTSTR lpszItemText )
{
	int nResult = -1;

	LVITEM lvItem;

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.cchTextMax	= STRING_LENGTH;
	lvItem.iItem		= SendMessage( g_hWndListView, LVM_GETITEMCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );
	lvItem.iSubItem		= 0;
	lvItem.pszText		= ( LPTSTR )lpszItemText;

	// Add item to list view window
	nResult = SendMessage( g_hWndListView, LVM_INSERTITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );

	return nResult;

} // End of function ListViewWindowAddItem

BOOL ListViewWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create list view window
	g_hWndListView = ::CreateWindowEx( LIST_VIEW_WINDOW_EXTENDED_STYLE, LIST_VIEW_WINDOW_CLASS_NAME, LIST_VIEW_WINDOW_TITLE, LIST_VIEW_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, NULL, hInstance, NULL );

	// Ensure that list view window was created
	if( g_hWndListView )
	{
		// Successfully created list view window
		LVCOLUMN lvColumn;
		int nWhichColumn;
		LPCTSTR lpszColumnTitles [] = LIST_VIEW_WINDOW_COLUMN_TITLES;

		// Set extended list view window style
		SendMessage( g_hWndListView, LVM_SETEXTENDEDLISTVIEWSTYLE, ( WPARAM )0, ( LPARAM )LIST_VIEW_WINDOW_EXTENDED_STYLE );

		// Clear list view column structure
		ZeroMemory( &lvColumn, sizeof( lvColumn ) );

		// Initialise list view column structure
		lvColumn.mask = LVCF_TEXT;

		// Loop through list view window columns
		for( nWhichColumn = 0; nWhichColumn < LIST_VIEW_WINDOW_NUMBER_OF_COLUMNS; nWhichColumn ++ )
		{
			// Update list view column structure for column
			lvColumn.pszText = ( LPTSTR )( lpszColumnTitles[ nWhichColumn ] );

			// Add column to list view window
			SendMessage( g_hWndListView, LVM_INSERTCOLUMN, ( WPARAM )nWhichColumn, ( LPARAM )&lvColumn );

		}; // End of loop through list view window columns

		// Update all list view window column widths
		ListViewWindowSetAllColumnWidths();

		// Update return value
		bResult = TRUE;

	} // End of successfully created list view window

	return bResult;

} // End of function ListViewWindowCreate

BOOL ListViewWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move list view window
	return MoveWindow( g_hWndListView, nLeft, nTop, nWidth, nHeight, bRepaint );

} // End of function ListViewWindowMove

BOOL ListViewWindowGetRect( LPRECT lpRect )
{
	// Get list view window rect
	return GetWindowRect( g_hWndListView, lpRect );

} // End of function ListViewWindowGetRect

int ListViewWindowSetAllColumnWidths( int nColumnWidth )
{
	int nResult = 0;

	int nWhichColumn;

	// Loop through list view window columns
	for( nWhichColumn = 0; nWhichColumn < LIST_VIEW_WINDOW_NUMBER_OF_COLUMNS; nWhichColumn ++ )
	{
		// Set list view window column width
		SendMessage( g_hWndListView, LVM_SETCOLUMNWIDTH, ( WPARAM )nWhichColumn, ( LPARAM )nColumnWidth );

	}; // End of loop through list view window columns

	return nResult;

} // End of function ListViewWindowSetAllColumnWidths

HWND ListViewWindowSetFocus()
{
	// Focus on list view window
	return SetFocus( g_hWndListView );

} // End of function ListViewWindowSetFocus
