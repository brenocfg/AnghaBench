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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetDefaultUserProfileDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserProfileDirectoryW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

BOOL _SHGetUserProfileDirectoryW(HANDLE hToken, LPWSTR szPath, LPDWORD lpcchPath)
{
    BOOL result;
    if (!hToken)
    {
        OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
        result = GetUserProfileDirectoryW(hToken, szPath, lpcchPath);
        CloseHandle(hToken);
    }
    else if ((INT) hToken == -1)
    {
        result = GetDefaultUserProfileDirectoryW(szPath, lpcchPath);
    }
    else
    {
        result = GetUserProfileDirectoryW(hToken, szPath, lpcchPath);
    }
    TRACE("_SHGetUserProfileDirectoryW returning %S\n", szPath);
    return result;
}