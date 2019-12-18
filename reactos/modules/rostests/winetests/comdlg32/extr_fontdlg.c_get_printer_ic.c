#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pPrinterName; int /*<<< orphan*/  pDriverName; } ;
typedef  TYPE_1__ PRINTER_INFO_2A ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateICA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EnumPrintersA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PRINTER_ENUM_LOCAL ; 

__attribute__((used)) static HDC get_printer_ic(void)
{
    PRINTER_INFO_2A *info;
    DWORD info_size, num_printers=0;
    BOOL ret;
    HDC result=NULL;

    EnumPrintersA(PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &info_size, &num_printers);

    if (info_size == 0)
        return NULL;

    info = HeapAlloc(GetProcessHeap(), 0, info_size);

    ret = EnumPrintersA(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE)info, info_size, &info_size, &num_printers);

    if (ret)
        result = CreateICA(info->pDriverName, info->pPrinterName, NULL, NULL);

    HeapFree(GetProcessHeap(), 0, info);

    return result;
}