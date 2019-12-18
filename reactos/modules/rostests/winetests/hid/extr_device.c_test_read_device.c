#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  overlapped ;
typedef  int /*<<< orphan*/  device_name ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USAGE ;
struct TYPE_9__ {int InputReportByteLength; } ;
struct TYPE_8__ {scalar_t__ hEvent; } ;
typedef  int /*<<< orphan*/  PHIDP_PREPARSED_DATA ;
typedef  TYPE_1__ OVERLAPPED ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_2__ HIDP_CAPS ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetOverlappedResult (scalar_t__,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTickCount () ; 
 scalar_t__ HIDP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  HID_USAGE_GENERIC_GAMEPAD ; 
 int /*<<< orphan*/  HID_USAGE_GENERIC_JOYSTICK ; 
 int HID_USAGE_PAGE_GENERIC ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int HidD_FreePreparsedData (int /*<<< orphan*/ ) ; 
 int HidD_GetPreparsedData (scalar_t__,int /*<<< orphan*/ *) ; 
 int HidD_GetProductString (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HidP_GetCaps (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int READ_MAX_TIME ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ResetEvent (scalar_t__) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int) ; 
 scalar_t__ get_device (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  process_data (TYPE_2__,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_read_device(void)
{
    PHIDP_PREPARSED_DATA ppd;
    HIDP_CAPS Caps;
    OVERLAPPED overlapped;
    WCHAR device_name[128];
    CHAR *data = NULL;
    DWORD read;
    BOOL rc;
    NTSTATUS status;
    DWORD timeout, tick, spent, max_time;
    char *report;

    USAGE device_usages[] = {HID_USAGE_GENERIC_JOYSTICK, HID_USAGE_GENERIC_GAMEPAD};
    HANDLE device = get_device(HID_USAGE_PAGE_GENERIC, device_usages, 2, GENERIC_READ);

    if (!device)
        device = get_device(0x0, NULL, 0x0, GENERIC_READ);

    if (!device)
    {
        trace("No device found for reading\n");
        return;
    }
    rc = HidD_GetProductString(device, device_name, sizeof(device_name));
    ok(rc, "Failed to get product string(0x%x)\n", GetLastError());
    trace("Read tests on device :%s\n",wine_dbgstr_w(device_name));

    rc = HidD_GetPreparsedData(device, &ppd);
    ok(rc, "Failed to get preparsed data(0x%x)\n", GetLastError());
    status = HidP_GetCaps(ppd, &Caps);
    ok(status == HIDP_STATUS_SUCCESS, "Failed to get Caps(0x%x)\n", status);
    data = HeapAlloc(GetProcessHeap(), 0, Caps.InputReportByteLength);

    memset(&overlapped, 0, sizeof(overlapped));
    overlapped.hEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
    if (winetest_interactive)
    {
        max_time = READ_MAX_TIME;
        timeout = 1000;
    }
    else
        max_time = timeout = 100;
    if (winetest_interactive)
        trace("Test your device for the next %i seconds\n", max_time/1000);
    report = HeapAlloc(GetProcessHeap(), 0, 3 * Caps.InputReportByteLength);
    tick = GetTickCount();
    spent = 0;
    do
    {
        ReadFile(device, data, Caps.InputReportByteLength, NULL, &overlapped);
        if (WaitForSingleObject(overlapped.hEvent, timeout) != WAIT_OBJECT_0)
        {
            ResetEvent(overlapped.hEvent);
            spent = GetTickCount() - tick;
            trace("REMAINING: %d ms\n", max_time - spent);
            continue;
        }
        ResetEvent(overlapped.hEvent);
        spent = GetTickCount() - tick;
        GetOverlappedResult(device, &overlapped, &read, FALSE);
        if (read)
        {
            int i;

            report[0] = 0;
            for (i = 0; i < read && i < Caps.InputReportByteLength; i++)
            {
                char bytestr[5];
                sprintf(bytestr, "%x ", (BYTE)data[i]);
                strcat(report, bytestr);
            }
            trace("Input report (%i): %s\n", read, report);

            process_data(Caps, ppd, data, read);
        }
        trace("REMAINING: %d ms\n", max_time - spent);
    } while(spent < max_time);

    CloseHandle(overlapped.hEvent);
    rc = HidD_FreePreparsedData(ppd);
    ok(rc, "Failed to free preparsed data(0x%x)\n", GetLastError());
    CloseHandle(device);
    HeapFree(GetProcessHeap(), 0, data);
    HeapFree(GetProcessHeap(), 0, report);
}