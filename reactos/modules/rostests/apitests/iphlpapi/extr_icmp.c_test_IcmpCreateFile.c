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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IcmpCloseHandle (scalar_t__) ; 
 scalar_t__ IcmpCreateFile () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
test_IcmpCreateFile(void)
{
    HANDLE hIcmp;

    SetLastError(0xDEADBEEF);
    hIcmp = IcmpCreateFile();
    ok(hIcmp != INVALID_HANDLE_VALUE, "IcmpCreateFile failed unexpectedly: %lu\n", GetLastError());

    if (hIcmp != INVALID_HANDLE_VALUE)
        IcmpCloseHandle(hIcmp);
}