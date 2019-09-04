#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwFileAttributes; scalar_t__* cFileName; scalar_t__* cAlternateFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  char WCHAR ;
typedef  int UINT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LB_DESCR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CharLowerW (char*) ; 
 int DDL_DIRECTORY ; 
 int DDL_DRIVES ; 
 int DDL_EXCLUSIVE ; 
 scalar_t__ DRIVE_NO_ROOT_DIR ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_NO_MORE_FILES ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int /*<<< orphan*/  FindClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindFirstFileW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetDriveTypeW (char*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 scalar_t__ LB_ERR ; 
 scalar_t__ LB_OKAY ; 
 int LISTBOX_FindFileStrPos (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ LISTBOX_InsertString (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcmpW (scalar_t__*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,scalar_t__*) ; 

__attribute__((used)) static LRESULT LISTBOX_Directory( LB_DESCR *descr, UINT attrib,
                                  LPCWSTR filespec, BOOL long_names )
{
    HANDLE handle;
    LRESULT ret = LB_OKAY;
    WIN32_FIND_DATAW entry;
    int pos;
    LRESULT maxinsert = LB_ERR;

    /* don't scan directory if we just want drives exclusively */
    if (attrib != (DDL_DRIVES | DDL_EXCLUSIVE)) {
        /* scan directory */
        if ((handle = FindFirstFileW(filespec, &entry)) == INVALID_HANDLE_VALUE)
        {
	     int le = GetLastError();
            if ((le != ERROR_NO_MORE_FILES) && (le != ERROR_FILE_NOT_FOUND)) return LB_ERR;
        }
        else
        {
            do
            {
                WCHAR buffer[270];
                if (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    static const WCHAR bracketW[]  = { ']',0 };
                    static const WCHAR dotW[] = { '.',0 };
                    if (!(attrib & DDL_DIRECTORY) ||
                        !strcmpW( entry.cFileName, dotW )) continue;
                    buffer[0] = '[';
                    if (!long_names && entry.cAlternateFileName[0])
                        strcpyW( buffer + 1, entry.cAlternateFileName );
                    else
                        strcpyW( buffer + 1, entry.cFileName );
                    strcatW(buffer, bracketW);
                }
                else  /* not a directory */
                {
#define ATTRIBS (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | \
                 FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE)

                    if ((attrib & DDL_EXCLUSIVE) &&
                        ((attrib & ATTRIBS) != (entry.dwFileAttributes & ATTRIBS)))
                        continue;
#undef ATTRIBS
                    if (!long_names && entry.cAlternateFileName[0])
                        strcpyW( buffer, entry.cAlternateFileName );
                    else
                        strcpyW( buffer, entry.cFileName );
                }
                if (!long_names) CharLowerW( buffer );
                pos = LISTBOX_FindFileStrPos( descr, buffer );
                if ((ret = LISTBOX_InsertString( descr, pos, buffer )) < 0)
                    break;
                if (ret <= maxinsert) maxinsert++; else maxinsert = ret;
            } while (FindNextFileW( handle, &entry ));
            FindClose( handle );
        }
    }
    if (ret >= 0)
    {
        ret = maxinsert;

        /* scan drives */
        if (attrib & DDL_DRIVES)
        {
            WCHAR buffer[] = {'[','-','a','-',']',0};
            WCHAR root[] = {'A',':','\\',0};
            int drive;
            for (drive = 0; drive < 26; drive++, buffer[2]++, root[0]++)
            {
                if (GetDriveTypeW(root) <= DRIVE_NO_ROOT_DIR) continue;
                if ((ret = LISTBOX_InsertString( descr, -1, buffer )) < 0)
                    break;
            }
        }
    }
    return ret;
}