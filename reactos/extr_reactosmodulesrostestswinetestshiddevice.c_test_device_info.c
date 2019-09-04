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
typedef  int /*<<< orphan*/  device_name ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Usage; int /*<<< orphan*/  UsagePage; } ;
typedef  int /*<<< orphan*/  PHIDP_PREPARSED_DATA ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ HIDP_CAPS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 scalar_t__ HIDP_STATUS_SUCCESS ; 
 int HidD_FreePreparsedData (int /*<<< orphan*/ ) ; 
 int HidD_GetPreparsedData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int HidD_GetProductString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HidP_GetCaps (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_device_info(HANDLE device)
{
    PHIDP_PREPARSED_DATA ppd;
    HIDP_CAPS Caps;
    NTSTATUS status;
    BOOL rc;
    WCHAR device_name[128];

    rc = HidD_GetPreparsedData(device, &ppd);
    ok(rc, "Failed to get preparsed data(0x%x)\n", GetLastError());
    status = HidP_GetCaps(ppd, &Caps);
    ok(status == HIDP_STATUS_SUCCESS, "Failed to get Caps(0x%x)\n", status);
    rc = HidD_GetProductString(device, device_name, sizeof(device_name));
    ok(rc, "Failed to get product string(0x%x)\n", GetLastError());
    trace("Found device %s (%02x, %02x)\n", wine_dbgstr_w(device_name), Caps.UsagePage, Caps.Usage);
    rc = HidD_FreePreparsedData(ppd);
    ok(rc, "Failed to free preparsed data(0x%x)\n", GetLastError());
}