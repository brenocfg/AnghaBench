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
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__* have_com ; 
 scalar_t__* have_file ; 
 scalar_t__* have_lpt ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pClosePort (scalar_t__) ; 
 scalar_t__ pOpenPort (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ClosePort(void)
{
    HANDLE  hPort;
    HANDLE  hPort2;
    LPWSTR  nameW = NULL;
    DWORD   res;
    DWORD   res2;


    if (!pOpenPort || !pClosePort) return;

    if (have_com[0]) {
        nameW = have_com;

        hPort = (HANDLE) 0xdeadbeef;
        res = pOpenPort(nameW, &hPort);
        hPort2 = (HANDLE) 0xdeadbeef;
        res2 = pOpenPort(nameW, &hPort2);

        if (res2 && (hPort2 != hPort)) {
            SetLastError(0xdeadbeef);
            res2 = pClosePort(hPort2);
            ok(res2, "got %u with %u (expected '!= 0')\n", res2, GetLastError());
        }

        if (res) {
            SetLastError(0xdeadbeef);
            res = pClosePort(hPort);
            ok(res, "got %u with %u (expected '!= 0')\n", res, GetLastError());
        }
    }


    if (have_lpt[0]) {
        nameW = have_lpt;

        hPort = (HANDLE) 0xdeadbeef;
        res = pOpenPort(nameW, &hPort);
        hPort2 = (HANDLE) 0xdeadbeef;
        res2 = pOpenPort(nameW, &hPort2);

        if (res2 && (hPort2 != hPort)) {
            SetLastError(0xdeadbeef);
            res2 = pClosePort(hPort2);
            ok(res2, "got %u with %u (expected '!= 0')\n", res2, GetLastError());
        }

        if (res) {
            SetLastError(0xdeadbeef);
            res = pClosePort(hPort);
            ok(res, "got %u with %u (expected '!= 0')\n", res, GetLastError());
        }
    }


    if (have_file[0]) {
        nameW = have_file;

        hPort = (HANDLE) 0xdeadbeef;
        res = pOpenPort(nameW, &hPort);
        hPort2 = (HANDLE) 0xdeadbeef;
        res2 = pOpenPort(nameW, &hPort2);

        if (res2 && (hPort2 != hPort)) {
            SetLastError(0xdeadbeef);
            res2 = pClosePort(hPort2);
            ok(res2, "got %u with %u (expected '!= 0')\n", res2, GetLastError());
        }

        if (res) {
            SetLastError(0xdeadbeef);
            res = pClosePort(hPort);
            ok(res, "got %u with %u (expected '!= 0')\n", res, GetLastError());
        }

    }

    if (0) {
        /* an invalid HANDLE crash native localspl.dll */

        SetLastError(0xdeadbeef);
        res = pClosePort(NULL);
        trace("got %u with %u\n", res, GetLastError());

        SetLastError(0xdeadbeef);
        res = pClosePort( (HANDLE) 0xdeadbeef);
        trace("got %u with %u\n", res, GetLastError());

        SetLastError(0xdeadbeef);
        res = pClosePort(INVALID_HANDLE_VALUE);
        trace("got %u with %u\n", res, GetLastError());
    }

}