#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ Length; char* Buffer; } ;
typedef  TYPE_1__* PLSA_UNICODE_STRING ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetComputerNameW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 int TRUE ; 
 int /*<<< orphan*/  lstrcmpW (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL
LsapIsLocalComputer(PLSA_UNICODE_STRING ServerName)
{
    DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
    BOOL Result;
    LPWSTR buf;

    if (ServerName == NULL || ServerName->Length == 0 || ServerName->Buffer == NULL)
        return TRUE;

    buf = HeapAlloc(GetProcessHeap(), 0, dwSize * sizeof(WCHAR));
    Result = GetComputerNameW(buf, &dwSize);
    if (Result && (ServerName->Buffer[0] == '\\') && (ServerName->Buffer[1] == '\\'))
        ServerName += 2;
    Result = Result && !lstrcmpW(ServerName->Buffer, buf);
    HeapFree(GetProcessHeap(), 0, buf);

    return Result;
}