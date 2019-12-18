#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_name ;
typedef  int /*<<< orphan*/  attributes ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int Size; int /*<<< orphan*/  VersionNumber; int /*<<< orphan*/  ProductID; int /*<<< orphan*/  VendorID; } ;
struct TYPE_5__ {int /*<<< orphan*/  Usage; int /*<<< orphan*/  UsagePage; } ;
typedef  int /*<<< orphan*/  PHIDP_PREPARSED_DATA ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ HIDP_CAPS ;
typedef  TYPE_2__ HIDD_ATTRIBUTES ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 scalar_t__ HIDP_STATUS_SUCCESS ; 
 int HidD_FreePreparsedData (int /*<<< orphan*/ ) ; 
 int HidD_GetAttributes (int /*<<< orphan*/ ,TYPE_2__*) ; 
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
    HIDD_ATTRIBUTES attributes;
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
    rc = HidD_GetAttributes(device, &attributes);
    ok(rc, "Failed to get device attributes (0x%x)\n", GetLastError());
    ok(attributes.Size == sizeof(attributes), "Unexpected HIDD_ATTRIBUTES size: %d\n", attributes.Size);
    trace("Device attributes: vid:%04x pid:%04x ver:%04x\n", attributes.VendorID, attributes.ProductID, attributes.VersionNumber);
}