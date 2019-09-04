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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetComputerNameW (int /*<<< orphan*/ ,int*) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 int TRUE ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpW (char*,int /*<<< orphan*/ ) ; 

BOOL ADVAPI_IsLocalComputer(LPCWSTR ServerName)
{
    DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
    BOOL Result;
    LPWSTR buf;

    if (!ServerName || !ServerName[0])
        return TRUE;

    buf = heap_alloc(dwSize * sizeof(WCHAR));
    Result = GetComputerNameW(buf,  &dwSize);
    if (Result && (ServerName[0] == '\\') && (ServerName[1] == '\\'))
        ServerName += 2;
    Result = Result && !lstrcmpW(ServerName, buf);
    heap_free(buf);

    return Result;
}