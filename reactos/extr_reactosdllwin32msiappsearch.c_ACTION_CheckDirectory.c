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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ACTION_CheckDirectory(MSIPACKAGE *package, LPCWSTR dir,
 LPWSTR *appValue)
{
    DWORD attr = GetFileAttributesW(dir);

    if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY))
    {
        TRACE("directory exists, returning %s\n", debugstr_w(dir));
        *appValue = strdupW(dir);
    }

    return ERROR_SUCCESS;
}