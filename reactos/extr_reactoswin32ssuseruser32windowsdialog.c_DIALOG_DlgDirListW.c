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
typedef  int /*<<< orphan*/  temp ;
typedef  char WCHAR ;
typedef  int UINT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_DIR ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CharLowerW (char*) ; 
 int /*<<< orphan*/  CharUpperW (char*) ; 
 int DDL_DIRECTORY ; 
 int DDL_DRIVES ; 
 int DDL_EXCLUSIVE ; 
 int DDL_POSTMSGS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LB_DIR ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SetCurrentDirectoryW (char*) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  TRACE (char*,char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* strchrW (char*,char) ; 
 char* strrchrW (char*,char) ; 

__attribute__((used)) static INT DIALOG_DlgDirListW( HWND hDlg, LPWSTR spec, INT idLBox,
                                INT idStatic, UINT attrib, BOOL combo )
{
    HWND hwnd;
    LPWSTR orig_spec = spec;
    WCHAR any[] = {'*','.','*',0};

#define SENDMSG(msg,wparam,lparam) \
    ((attrib & DDL_POSTMSGS) ? PostMessageW( hwnd, msg, wparam, lparam ) \
                             : SendMessageW( hwnd, msg, wparam, lparam ))

    TRACE("%p %s %d %d %04x\n", hDlg, debugstr_w(spec), idLBox, idStatic, attrib );

    /* If the path exists and is a directory, chdir to it */
    if (!spec || !spec[0] || SetCurrentDirectoryW( spec )) spec = any;
    else
    {
        WCHAR *p, *p2;
        p = spec;
        if ((p2 = strchrW( p, ':' ))) p = p2 + 1;
        if ((p2 = strrchrW( p, '\\' ))) p = p2;
        if ((p2 = strrchrW( p, '/' ))) p = p2;
        if (p != spec)
        {
            WCHAR sep = *p;
            *p = 0;
            if (!SetCurrentDirectoryW( spec ))
            {
                *p = sep;  /* Restore the original spec */
                return FALSE;
            }
            spec = p + 1;
        }
    }

    TRACE( "mask=%s\n", spec );

    if (idLBox && ((hwnd = GetDlgItem( hDlg, idLBox )) != 0))
    {
        if (attrib == DDL_DRIVES) attrib |= DDL_EXCLUSIVE;

        SENDMSG( combo ? CB_RESETCONTENT : LB_RESETCONTENT, 0, 0 );
        if (attrib & DDL_DIRECTORY)
        {
            if (!(attrib & DDL_EXCLUSIVE))
            {
                SENDMSG( combo ? CB_DIR : LB_DIR,
                         attrib & ~(DDL_DIRECTORY | DDL_DRIVES),
                         (LPARAM)spec );
            }
            SENDMSG( combo ? CB_DIR : LB_DIR,
                   (attrib & (DDL_DIRECTORY | DDL_DRIVES)) | DDL_EXCLUSIVE,
                   (LPARAM)any );
        }
        else
        {
            SENDMSG( combo ? CB_DIR : LB_DIR, attrib, (LPARAM)spec );
        }
    }

    /* Convert path specification to uppercase */
    if (spec) CharUpperW(spec);

    if (idStatic && ((hwnd = GetDlgItem( hDlg, idStatic )) != 0))
    {
        WCHAR temp[MAX_PATH];
        GetCurrentDirectoryW( sizeof(temp)/sizeof(WCHAR), temp );
        CharLowerW( temp );
        /* Can't use PostMessage() here, because the string is on the stack */
        SetDlgItemTextW( hDlg, idStatic, temp );
    }

    if (orig_spec && (spec != orig_spec))
    {
        /* Update the original file spec */
        WCHAR *p = spec;
        while ((*orig_spec++ = *p++));
    }

    return TRUE;
#undef SENDMSG
}