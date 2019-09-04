#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pagesetup_data ;
struct TYPE_8__ {int /*<<< orphan*/  pPortName; int /*<<< orphan*/  pPrinterName; int /*<<< orphan*/  pDriverPath; } ;
typedef  TYPE_1__ PRINTER_INFO_2W ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DRIVER_INFO_3W ;
typedef  TYPE_1__ DEVMODEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_OUT_BUFFER ; 
 int DocumentPropertiesW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetPrinterDriverW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GetPrinterW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OpenPrinterW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagesetup_set_devmode (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pagesetup_set_devnames (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL pagesetup_change_printer(LPWSTR name, pagesetup_data *data)
{
    HANDLE hprn;
    DWORD needed;
    PRINTER_INFO_2W *prn_info = NULL;
    DRIVER_INFO_3W *drv_info = NULL;
    DEVMODEW *dm = NULL;
    BOOL retval = FALSE;

    if(!OpenPrinterW(name, &hprn, NULL))
    {
        ERR("Can't open printer %s\n", debugstr_w(name));
        goto end;
    }

    GetPrinterW(hprn, 2, NULL, 0, &needed);
    prn_info = HeapAlloc(GetProcessHeap(), 0, needed);
    GetPrinterW(hprn, 2, (LPBYTE)prn_info, needed, &needed);
    GetPrinterDriverW(hprn, NULL, 3, NULL, 0, &needed);
    drv_info = HeapAlloc(GetProcessHeap(), 0, needed);
    if(!GetPrinterDriverW(hprn, NULL, 3, (LPBYTE)drv_info, needed, &needed))
    {
        ERR("GetPrinterDriverA failed for %s, fix your config!\n", debugstr_w(prn_info->pPrinterName));
        goto end;
    }
    ClosePrinter(hprn);

    needed = DocumentPropertiesW(0, 0, name, NULL, NULL, 0);
    if(needed == -1)
    {
        ERR("DocumentProperties fails on %s\n", debugstr_w(name));
        goto end;
    }

    dm = HeapAlloc(GetProcessHeap(), 0, needed);
    DocumentPropertiesW(0, 0, name, dm, NULL, DM_OUT_BUFFER);

    pagesetup_set_devmode(data, dm);
    pagesetup_set_devnames(data, drv_info->pDriverPath, prn_info->pPrinterName,
                           prn_info->pPortName);

    retval = TRUE;
end:
    HeapFree(GetProcessHeap(), 0, dm);
    HeapFree(GetProcessHeap(), 0, prn_info);
    HeapFree(GetProcessHeap(), 0, drv_info);
    return retval;
}