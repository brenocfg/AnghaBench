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
typedef  int LONG ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DEVMODEA ;

/* Variables and functions */
 int ClosePrinter (scalar_t__) ; 
 int /*<<< orphan*/  DM_OUT_BUFFER ; 
 int DocumentPropertiesA (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IDOK ; 
 int OpenPrinterA (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  default_printer ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  test_DEVMODEA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_DocumentProperties(void)
{
    HANDLE hprn;
    LONG dm_size, ret;
    DEVMODEA *dm;
    char empty_str[] = "";

    if (!default_printer)
    {
        skip("There is no default printer installed\n");
        return;
    }

    hprn = 0;
    ret = OpenPrinterA(default_printer, &hprn, NULL);
    if (!ret)
    {
        skip("Unable to open the default printer (%s)\n", default_printer);
        return;
    }
    ok(hprn != 0, "wrong hprn %p\n", hprn);

    dm_size = DocumentPropertiesA(0, hprn, NULL, NULL, NULL, 0);
    trace("DEVMODEA required size %d\n", dm_size);
    ok(dm_size >= sizeof(DEVMODEA), "unexpected DocumentPropertiesA ret value %d\n", dm_size);

    dm = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dm_size);

    ret = DocumentPropertiesA(0, hprn, NULL, dm, dm, DM_OUT_BUFFER);
    ok(ret == IDOK, "DocumentPropertiesA ret value %d != expected IDOK\n", ret);

    ret = DocumentPropertiesA(0, hprn, empty_str, dm, dm, DM_OUT_BUFFER);
    ok(ret == IDOK, "DocumentPropertiesA ret value %d != expected IDOK\n", ret);

    test_DEVMODEA(dm, dm_size, default_printer);

    HeapFree(GetProcessHeap(), 0, dm);

    SetLastError(0xdeadbeef);
    ret = ClosePrinter(hprn);
    ok(ret, "ClosePrinter error %d\n", GetLastError());
}