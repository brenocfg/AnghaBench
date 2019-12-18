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
typedef  int /*<<< orphan*/  PWLAN_INTERFACE_INFO_LIST ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ WlanEnumInterfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void WlanEnumInterfaces_test(void)
{
    DWORD ret;
    PWLAN_INTERFACE_INFO_LIST pInterfaceList;

    /* invalid pReserved */
    ret = WlanEnumInterfaces((HANDLE) -1, (PVOID) 1, &pInterfaceList);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid pInterfaceList */
    ret = WlanEnumInterfaces((HANDLE) -1, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");    
}