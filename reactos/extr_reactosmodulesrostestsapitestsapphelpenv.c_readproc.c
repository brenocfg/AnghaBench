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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static BOOL readproc(HANDLE proc, LPVOID address, PVOID target, DWORD size)
{
    SIZE_T dwRead;
    if (ReadProcessMemory(proc, address, target, size, &dwRead))
    {
        ok(dwRead == size, "Expected to read %u bytes, got %lu\n", size, dwRead);
        return dwRead == size;
    }
    ok(0, "RPM failed with %u\n", GetLastError());
    return FALSE;
}