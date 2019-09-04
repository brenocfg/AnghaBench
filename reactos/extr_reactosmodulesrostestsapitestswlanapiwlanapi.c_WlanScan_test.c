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
typedef  int /*<<< orphan*/  WLAN_RAW_DATA ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  DOT11_SSID ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  InterfaceGuid ; 
 scalar_t__ WlanScan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void WlanScan_test(void)
{
    DWORD ret;
    DOT11_SSID Ssid;
    WLAN_RAW_DATA RawData;
    
    /* invalid pReserved */
    ret = WlanScan((HANDLE) -1, &InterfaceGuid, &Ssid, &RawData, (PVOID) 1);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");
    
    /* invalid InterfaceGuid */
    ret = WlanScan((HANDLE) -1, NULL, &Ssid, &RawData, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid hClientHandle */
    ret = WlanScan(NULL, &InterfaceGuid, &Ssid, &RawData, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");
}