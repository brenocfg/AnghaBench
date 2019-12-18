#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  CB_GETLBTEXTLEN ; 
 int /*<<< orphan*/  CP_ACP ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_GETTEXTLEN ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/ * strchrW (char*,char) ; 
 size_t strlenW (char*) ; 

__attribute__((used)) static BOOL DIALOG_DlgDirSelect( HWND hwnd, LPWSTR str, INT len,
                                 INT id, BOOL unicode, BOOL combo )
{
    WCHAR *buffer, *ptr;
    INT item, size;
    BOOL ret;
    HWND listbox = GetDlgItem( hwnd, id );

    TRACE("%p %s %d\n", hwnd, unicode ? debugstr_w(str) : debugstr_a((LPSTR)str), id );
    if (!listbox) return FALSE;

    item = SendMessageW(listbox, combo ? CB_GETCURSEL : LB_GETCURSEL, 0, 0 );
    if (item == LB_ERR) return FALSE;

    size = SendMessageW(listbox, combo ? CB_GETLBTEXTLEN : LB_GETTEXTLEN, item, 0 );
    if (size == LB_ERR) return FALSE;

    if (!(buffer = HeapAlloc( GetProcessHeap(), 0, (size+2) * sizeof(WCHAR) ))) return FALSE;

    SendMessageW( listbox, combo ? CB_GETLBTEXT : LB_GETTEXT, item, (LPARAM)buffer );

    if ((ret = (buffer[0] == '[')))  /* drive or directory */
    {
        if (buffer[1] == '-')  /* drive */
        {
            buffer[3] = ':';
            buffer[4] = 0;
            ptr = buffer + 2;
        }
        else
        {
            buffer[strlenW(buffer)-1] = '\\';
            ptr = buffer + 1;
        }
    }
    else
    {
        /* Filenames without a dot extension must have one tacked at the end */
        if (strchrW(buffer, '.') == NULL)
        {
            buffer[strlenW(buffer)+1] = '\0';
            buffer[strlenW(buffer)] = '.';
        }
        ptr = buffer;
    }

    if (!unicode)
    {
        if (len > 0 && !WideCharToMultiByte( CP_ACP, 0, ptr, -1, (LPSTR)str, len, 0, 0 ))
            ((LPSTR)str)[len-1] = 0;
    }
    else lstrcpynW( str, ptr, len );
    HeapFree( GetProcessHeap(), 0, buffer );
    TRACE("Returning %d %s\n", ret, unicode ? debugstr_w(str) : debugstr_a((LPSTR)str) );
    return ret;
}