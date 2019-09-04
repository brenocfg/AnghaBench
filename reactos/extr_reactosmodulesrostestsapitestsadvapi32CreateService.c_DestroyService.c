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
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ DNS_ERROR_RCODE_NXRRSET ; 
 scalar_t__ DeleteService (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void DestroyService(SC_HANDLE hService)
{
    LONG ret;

    if (!hService)
        return;
    SetLastError(DNS_ERROR_RCODE_NXRRSET);
    ret = DeleteService(hService);
    ok(ret == TRUE, "DeleteService returned %ld, expected 1\n", ret);
    ok(GetLastError() == DNS_ERROR_RCODE_NXRRSET /* win7 */
        || GetLastError() == ERROR_SUCCESS /* win2k3 */, "DeleteService GetLastError()=0x%08lx\n", GetLastError());

    CloseServiceHandle(hService);
}