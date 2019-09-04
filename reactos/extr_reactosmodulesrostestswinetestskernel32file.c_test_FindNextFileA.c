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
typedef  int /*<<< orphan*/  WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int ERROR_NO_MORE_FILES ; 
 scalar_t__ FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ FindNextFileA (scalar_t__,int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ TRUE ; 
 char get_windows_drive () ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_FindNextFileA(void)
{
    HANDLE handle;
    WIN32_FIND_DATAA search_results;
    int err;
    char buffer[5] = "C:\\*";

    buffer[0] = get_windows_drive();
    handle = FindFirstFileA(buffer,&search_results);
    ok ( handle != INVALID_HANDLE_VALUE, "FindFirstFile on C:\\* should succeed\n" );
    while (FindNextFileA(handle, &search_results))
    {
        /* get to the end of the files */
    }
    ok ( FindClose(handle) == TRUE, "Failed to close handle\n");
    err = GetLastError();
    ok ( err == ERROR_NO_MORE_FILES, "GetLastError should return ERROR_NO_MORE_FILES\n");
}