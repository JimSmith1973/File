// ListViewWindow.cpp

#include "ListViewWindow.h"

// Global variables
static HWND g_hWndListView;

BOOL IsListViewWindow( HWND hWndQuery )
{
	return( hWndQuery == g_hWndListView );
}
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

int CALLBACK ListViewWindowCompare( LPARAM lParam1, LPARAM lParam2, LPARAM lParamColumn )
{
	int nResult = 0;

	LVITEM lvItem;

	// Allocate string memory
	LPTSTR lpszItem1 = new char[ STRING_LENGTH ];
	LPTSTR lpszItem2 = new char[ STRING_LENGTH ];

	// Clear list view item structure
	ZeroMemory( &lvItem, sizeof( lvItem ) );

	// Initialise list view item structure
	lvItem.mask			= LVIF_TEXT;
	lvItem.iSubItem		= lParamColumn;
	lvItem.cchTextMax	= STRING_LENGTH;

	// Update list view item structure for first item
	lvItem.iItem	= lParam1;
	lvItem.pszText	= lpszItem1;

	// Get first item text
	if( SendMessage( g_hWndListView, LVM_GETITEMTEXT, ( WPARAM )lParam1, ( LPARAM )&lvItem ) )
	{
		// Successfully got first item text

		// Update list view item structure for second item
		lvItem.iItem	= lParam2;
		lvItem.pszText	= lpszItem2;

		// Get second item text
		if( SendMessage( g_hWndListView, LVM_GETITEMTEXT, ( WPARAM )lParam2, ( LPARAM )&lvItem ) )
		{
			// Successfully got second item text

			// Compare item texts
			nResult = lstrcmp( lpszItem1, lpszItem2 );

		} // End of successfully got second item text

	} // End of successfully got first item text

	// See if the modified column is being sorted
	if( lParamColumn == LIST_VIEW_WINDOW_MODIFIED_COLUMN_ID )
	{
		// The modified column is being sorted

		// Invert result (so that most recent itema appear at the top)
		nResult = ( 0 - nResult );

	} // End of the modified column is being sorted

	// Free string memory
	delete [] lpszItem1;
	delete [] lpszItem2;

	return nResult;

} // End of function ListViewWindowCompare

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

BOOL ListViewWindowGetRect( LPRECT lpRect )
{
	// Get list view window rect
	return GetWindowRect( g_hWndListView, lpRect );

} // End of function ListViewWindowGetRect

BOOL ListViewWindowGetItemPath( int nWhichItem, int nWhichSubItem, LPTSTR lpszItemPath )
{
	BOOL bResult = FALSE;

	// Get current folder into item path
	if( GetCurrentDirectory( STRING_LENGTH, lpszItemPath ) )
	{
		// Successfully got current folder into item path
		LVITEM lvItem;

		// Allocate string memory
		LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

		// Clear list view item structure
		ZeroMemory( &lvItem, sizeof( lvItem ) );

		// Initialise list view item structure
		lvItem.mask			= LVIF_TEXT;
		lvItem.iItem		= nWhichItem;
		lvItem.iSubItem		= nWhichSubItem;
		lvItem.pszText		= lpszItemText;
		lvItem.cchTextMax	= STRING_LENGTH;

		// Get item text
		if( SendMessage( g_hWndListView, LVM_GETITEMTEXT, ( WPARAM )nWhichItem, ( LPARAM )&lvItem ) )
		{
			// Successfully got item text

			// Ensure that item path ends with a back-slash
			if( lpszItemPath[ lstrlen( lpszItemPath ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
			{
				// Item path does not end with a back-slash

				// Append a back-slash onto item path
				lstrcat( lpszItemPath, ASCII_BACK_SLASH_STRING );

			} // End of item path does not end with a back-slash

			// See if item is a folder
			if( lpszItemText[ 0 ] == LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_PREFIX )
			{
				// Item is a folder

				// Update item path
				lstrcat( lpszItemPath, ( lpszItemText + sizeof( LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_PREFIX ) ) );

			} // End of item is a folder
			else
			{
				// Item is a file

				// Update item path
				lstrcat( lpszItemPath, lpszItemText );

			} // End of item is a file

			// Update return value
			bResult = TRUE;

		} // End of successfully got item text

		// Free string memory
		delete [] lpszItemText;

	} // End of successfully got current folder into item path

	return bResult;

} // End of function ListViewWindowGetItemPath

BOOL ListViewWindowHandleNotifyMessage( WPARAM, LPARAM lParam, BOOL( *lpStatusFunction )( LPCTSTR lpszStatusMessage ))
{
	BOOL bResult = FALSE;

	LPNMLISTVIEW lpNmListView;

	// Get list view notify message handler
	lpNmListView = ( LPNMLISTVIEW )lParam;

	// Select notify message
	switch( lpNmListView->hdr.code )
	{
		case NM_DBLCLK:
		{
			// A double click notify message

			// Allocate string memory
			LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

			// Get item path
			if( ListViewWindowGetItemPath( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemPath ) )
			{
				// Successfully got item path

				// See if item is a folder
				if( GetFileAttributes( lpszItemPath ) & FILE_ATTRIBUTE_DIRECTORY )
				{
					// Item is a folder

					// Populate to folder
					ListViewWindowPopulate( lpszItemPath, ALL_FILES_FILTER, lpStatusFunction );

				} // End of item is a folder
				else
				{
					// Item is a file

					// Open file
					if( ( static_cast<int>( reinterpret_cast<uintptr_t>( ShellExecute( NULL, SHELL_EXECUTE_OPEN_COMMAND, lpszItemPath, NULL, NULL, SW_SHOWNORMAL ) ) ) ) <= 32 )
					{
						// Unable to open file

						// Allocate string memory
						LPTSTR lpszErrorMessage = new char[ STRING_LENGTH ];

						// Format error message
						wsprintf( lpszErrorMessage, UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING, lpszItemPath );

						// Display error message
						MessageBox( 0, lpszErrorMessage, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

						// Free string memory
						delete [] lpszErrorMessage;

					} // End of unable to open file

				} // End of item is a file

				// Update return value
				bResult = TRUE;

			} // End of successfully got item path

			// Free string memory
			delete [] lpszItemPath;

			// Break out of switch
			break;

		} // End of a double click notify message
		case LVN_COLUMNCLICK:
		{
			// A column click notify message

			// Sort the list view
			::SendMessage( g_hWndListView, LVM_SORTITEMSEX, ( WPARAM )( lpNmListView->iSubItem ), ( LPARAM )&ListViewWindowCompare );

			// Break out of switch
			break;

		} // End of a column click notify message
/*		case LVN_ITEMCHANGED:
		{
			// A list view item changed notify message

			// See if item has changed to selected
			if( ( lpNmListView->uNewState ^ lpNmListView->uOldState ) & LVIS_SELECTED )
			{
				// Item has changed to selected

				// Allocate string memory
				LPTSTR lpszItemPath = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get item path
				if( ListViewWindowGetItemPath( lpNmListView->iItem, lpNmListView->iSubItem, lpszItemPath ) )
				{
					// Successfully got item path

					// Show item path
					( *lpStatusFunction )( lpszItemPath );

					// Update return value
					bResult = TRUE;

				} // End of successfully got item path

				// Free string memory
				delete [] lpszItemPath;

			} // End of item has changed to selected

			// Break out of switch
			break;

		} // End of a list view item changed notify message
*/
	}; // End of selection for notify message

	return bResult;

} // End of function ListViewWindowHandleNotifyMessage

BOOL ListViewWindowMove( int nLeft, int nTop, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move list view window
	return MoveWindow( g_hWndListView, nLeft, nTop, nWidth, nHeight, bRepaint );

} // End of function ListViewWindowMove

int ListViewWindowPopulate( LPCTSTR lpszFileFilter, BOOL( *lpStatusFunction )( LPCTSTR lpszStatusMessage ) )
{
	int nResult = -1;

	// Allocate string memory
	LPTSTR lpszFolderPath = new char[ STRING_LENGTH + sizeof( char ) ];

	// Get current folder path
	if( GetCurrentDirectory( STRING_LENGTH, lpszFolderPath ) )
	{
		// Successfully got current folder path

		// Populate list view window
		nResult = ListViewWindowPopulate( lpszFolderPath, lpszFileFilter, lpStatusFunction );

	} // End of successfully got current folder path

	// Free string memory
	delete [] lpszFolderPath;

	return nResult;

} // End of function ListViewWindowPopulate

int ListViewWindowPopulate( LPCTSTR lpszFolderPath, LPCTSTR lpszFileFilter, BOOL( *lpStatusFunction )( LPCTSTR lpszStatusMessage ) )
{
	int nResult = -1;

	WIN32_FIND_DATA wfd;
	HANDLE hFind;

	// Allocate string memory
	LPTSTR lpszFullSearchPattern	= new char[ STRING_LENGTH + sizeof( char ) ];
	LPTSTR lpszStatusMessage		= new char[ STRING_LENGTH + sizeof( char ) ];

	// Copy parent folder path into full search pattern
	lstrcpy( lpszFullSearchPattern, lpszFolderPath );

	// Ensure that full search pattern ends with a back-slash
	if( lpszFullSearchPattern[ lstrlen( lpszFullSearchPattern ) - sizeof( char ) ] != ASCII_BACK_SLASH_CHARACTER )
	{
		// Full search pattern does not end with a back-slash

		// Append a back-slash onto full search pattern
		lstrcat( lpszFullSearchPattern, ASCII_BACK_SLASH_STRING );

	} // End of full search pattern does not end with a back-slash

	// Append file filter onto full search pattern
	lstrcat( lpszFullSearchPattern, lpszFileFilter );

	// Format status message
	wsprintf( lpszStatusMessage, LIST_VIEW_WINDOW_POPULATING_STATUS_MESSAGE_FORMAT_STRING, lpszFullSearchPattern );

	// Show status message
	( *lpStatusFunction )( lpszStatusMessage );

	// Find first item
	hFind = FindFirstFile( lpszFullSearchPattern, &wfd );

	// Ensure that first item was found
	if( hFind != INVALID_HANDLE_VALUE )
	{
		// Successfully found first item
		LVITEM lvItem;
		SYSTEMTIME stModified;

		// Allocate string memory
		LPTSTR lpszDisplayText	= new char[ STRING_LENGTH + sizeof( char ) ];
		LPTSTR lpszModified		= new char[ STRING_LENGTH + sizeof( char ) ];

		// Clear list view item structure
		ZeroMemory( &lvItem, sizeof( lvItem ) );

		// Initialise list view item structure
		lvItem.mask			= LVIF_TEXT;
		lvItem.cchTextMax	= STRING_LENGTH;
		lvItem.iItem		= 0;

		// Set current folder
		SetCurrentDirectory( lpszFolderPath );

		// Delete all items from list view window
		SendMessage( g_hWndListView, LVM_DELETEALLITEMS, ( WPARAM )NULL, ( LPARAM )NULL );

		// Initialise result
		nResult = 0;

		// Loop through all items
		do
		{
			// Clear display text
			lpszDisplayText[ 0 ] = ( char )NULL;

			// See if found item is a folder
			if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// Found item is a folder

				// Ensure that found item is not dots
				if( ( lstrcmp( wfd.cFileName, LIST_VIEW_WINDOW_CURRENT_FOLDER_NAME ) != 0 ) && ( lstrcmp( wfd.cFileName, LIST_VIEW_WINDOW_PARENT_FOLDER_NAME ) != 0 ) )
				{
					// Found item is not dots

					// Format display item text
					wsprintf( lpszDisplayText, LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_FORMAT_STRING, LIST_VIEW_WINDOW_FOLDER_DISPLAY_TEXT_PREFIX, wfd.cFileName );

				} // End of found item is not dots

			} // End of found item is a folder
			else
			{
				// Found item is a file

				// Use item name as display item text
				lstrcpy( lpszDisplayText, wfd.cFileName );

			} // End of found item is a file

			// Ensure that display text is valid
			if( lpszDisplayText[ 0 ] )
			{
				// Display text is valid

				// Update list view item structure for file name
				lvItem.iSubItem		= LIST_VIEW_WINDOW_NAME_COLUMN_ID;
				lvItem.pszText		= lpszDisplayText;

				// Add item to list view window
				lvItem.iItem = SendMessage( g_hWndListView, LVM_INSERTITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );

				// Ensure that item was added to list view window
				if( lvItem.iItem >= 0 )
				{
					// Successfully added item to list view window

					// Get modified system time
					FileTimeToSystemTime( &( wfd.ftLastWriteTime ), &stModified );

					// Format modified text
					wsprintf( lpszModified, LIST_VIEW_WINDOW_MODIFIED_TEXT_FORMAT_STRING, stModified.wYear, stModified.wMonth, stModified.wDay, stModified.wHour, stModified.wMinute, stModified.wSecond );

					// Update list view item structure for modified text
					lvItem.iSubItem		= LIST_VIEW_WINDOW_MODIFIED_COLUMN_ID;
					lvItem.pszText		= lpszModified;

					// Show modified text
					SendMessage( g_hWndListView, LVM_SETITEM, ( WPARAM )lvItem.iItem, ( LPARAM )&lvItem );

					// Advance to next item
					lvItem.iItem ++;

					// Update return value
					nResult ++;

				} // End of successfully added item to list view window

			} // End of display text is valid

		} while( FindNextFile( hFind, &wfd ) != 0 ); // End of loop through all items

		// Update all list view window column widths
		ListViewWindowSetAllColumnWidths();

		// Format status message
		wsprintf( lpszStatusMessage, LIST_VIEW_WINDOW_POPULATED_STATUS_MESSAGE_FORMAT_STRING, lpszFolderPath, nResult );

		// Show status message
		( *lpStatusFunction )( lpszStatusMessage );

		// Close file find
		FindClose( hFind );

		// Free string memory
		delete [] lpszDisplayText;
		delete [] lpszModified;

	} // End of successfully found first item
	else
	{
		// Unable to find first item

		// Format status message
		wsprintf( lpszStatusMessage, LIST_VIEW_WINDOW_UNABLE_TO_OPEN_FOLDER_STATUS_MESSAGE_FORMAT_STRING, lpszFolderPath );

		// Show status message
		( *lpStatusFunction )( lpszStatusMessage );

		// Indicate error
		MessageBeep( MB_ICONERROR );

	} // End of unable to find first item

	// Free string memory
	delete [] lpszFullSearchPattern;
	delete [] lpszStatusMessage;

	return nResult;

} // End of function ListViewWindowPopulate

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
