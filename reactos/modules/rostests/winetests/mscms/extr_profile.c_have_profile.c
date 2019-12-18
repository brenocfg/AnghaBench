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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  pGetColorDirectoryA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL have_profile(void)
{
    char glob[MAX_PATH + sizeof("\\*.icm")];
    DWORD size = MAX_PATH;
    HANDLE handle;
    WIN32_FIND_DATAA data;

    if (!pGetColorDirectoryA( NULL, glob, &size )) return FALSE;
    lstrcatA( glob, "\\*.icm" );
    handle = FindFirstFileA( glob, &data );
    if (handle == INVALID_HANDLE_VALUE) return FALSE;
    FindClose( handle );
    return TRUE;
}