#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_7__ {TYPE_3__* Sid; } ;
struct TYPE_9__ {TYPE_1__ User; } ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PTOKEN_USER ;
typedef  int /*<<< orphan*/  PHKEY ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenProcess (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_VM_READ ; 
 int READ_CONTROL ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlConvertSidToUnicodeString (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_2__*) ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int TRUE ; 
 int /*<<< orphan*/  TokenUser ; 

__attribute__((used)) static BOOL
OpenUserRegistryPathPerProcessId(DWORD ProcessId,
                                 PHKEY hResult,
                                 REGSAM samDesired)
{
    BOOL bRet = TRUE;
    HANDLE hProcessToken = NULL;
    HANDLE hProcess;
    BYTE Buffer[256];
    DWORD Length = 0;
    UNICODE_STRING SidName;
    PTOKEN_USER TokUser;

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | READ_CONTROL, FALSE, ProcessId);
    if (!hProcess)
    {
        DPRINT1("Error: OpenProcess failed(0x%x)\n", GetLastError());
        return FALSE;
    }

    if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
    {
        DPRINT1("Error: OpenProcessToken failed(0x%x)\n", GetLastError());
        CloseHandle(hProcess);
        return FALSE;
    }

    if (!GetTokenInformation(hProcessToken, TokenUser, (PVOID)Buffer, sizeof(Buffer), &Length))
    {
        DPRINT1("Error: GetTokenInformation failed(0x%x)\n",GetLastError());
        CloseHandle(hProcessToken);
        CloseHandle(hProcess);
        return FALSE;
    }

    TokUser = ((PTOKEN_USER)Buffer)->User.Sid;
    if (!NT_SUCCESS(RtlConvertSidToUnicodeString(&SidName, TokUser, TRUE)))
    {
        DPRINT1("Error: RtlConvertSidToUnicodeString failed(0x%x)\n", GetLastError());
        CloseHandle(hProcessToken);
        CloseHandle(hProcess);
        return FALSE;
    }

    /*
     * Might fail for LiveCD... Why ? Because only HKU\.DEFAULT exists.
     */
    bRet = (RegOpenKeyExW(HKEY_USERS,
                          SidName.Buffer,
                          0,
                          samDesired,
                          hResult) == ERROR_SUCCESS);

    RtlFreeUnicodeString(&SidName);

    CloseHandle(hProcessToken);
    CloseHandle(hProcess);

    return bRet;
}