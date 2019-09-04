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
typedef  void* HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int ClosePrinter (void*) ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ GetLastError () ; 
 int OpenPrinterA (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  default_printer ; 
 scalar_t__ is_spooler_deactivated (int,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 

__attribute__((used)) static void test_ClosePrinter(void)
{
    HANDLE printer = 0;
    BOOL res;

    /* NULL is handled */
    SetLastError(0xdeadbeef);
    res = ClosePrinter(NULL);
    ok(!res && (GetLastError() == ERROR_INVALID_HANDLE),
        "got %d with %d (expected FALSE with ERROR_INVALID_HANDLE)\n",
        res, GetLastError());

    /* A random value as HANDLE is handled */
    SetLastError(0xdeadbeef);
    res = ClosePrinter( (void *) -1);
    if (is_spooler_deactivated(res, GetLastError())) return;
    ok(!res && (GetLastError() == ERROR_INVALID_HANDLE),
        "got %d with %d (expected FALSE with ERROR_INVALID_HANDLE)\n",
         res, GetLastError());


    /* Normal use (The Spooler service is needed) */
    SetLastError(0xdeadbeef);
    res = OpenPrinterA(default_printer, &printer, NULL);
    if (is_spooler_deactivated(res, GetLastError())) return;
    if (res)
    {
        SetLastError(0xdeadbeef);
        res = ClosePrinter(printer);
        ok(res, "got %d with %d (expected TRUE)\n", res, GetLastError());


        /* double free is handled */
        SetLastError(0xdeadbeef);
        res = ClosePrinter(printer);
        ok(!res && (GetLastError() == ERROR_INVALID_HANDLE),
            "got %d with %d (expected FALSE with ERROR_INVALID_HANDLE)\n",
            res, GetLastError());

    }
}