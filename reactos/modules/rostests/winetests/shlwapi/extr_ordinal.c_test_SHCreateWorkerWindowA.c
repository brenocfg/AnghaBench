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
typedef  int /*<<< orphan*/  cliA ;
struct TYPE_4__ {int style; int cbClsExtra; int cbWndExtra; int lpszMenuName; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int LONG_PTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetClassInfoA (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetClassNameA (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int GetWindowLongA (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrA (scalar_t__,int /*<<< orphan*/ ) ; 
 int WS_EX_LAYOUTRTL ; 
 int WS_EX_TOOLWINDOW ; 
 int WS_EX_WINDOWEDGE ; 
 scalar_t__ lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pSHCreateWorkerWindowA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_SHCreateWorkerWindowA(void)
{
    WNDCLASSA cliA;
    char classA[20];
    HWND hwnd;
    LONG_PTR ret;
    BOOL res;

    hwnd = pSHCreateWorkerWindowA(0, NULL, 0, 0, 0, 0);
    ok(hwnd != 0, "expected window\n");

    GetClassNameA(hwnd, classA, 20);
    ok(lstrcmpA(classA, "WorkerA") == 0, "expected WorkerA class, got %s\n", classA);

    ret = GetWindowLongPtrA(hwnd, 0);
    ok(ret == 0, "got %ld\n", ret);

    /* class info */
    memset(&cliA, 0, sizeof(cliA));
    res = GetClassInfoA(GetModuleHandleA("shlwapi.dll"), "WorkerA", &cliA);
    ok(res, "failed to get class info\n");
    ok(cliA.style == 0, "got 0x%08x\n", cliA.style);
    ok(cliA.cbClsExtra == 0, "got %d\n", cliA.cbClsExtra);
    ok(cliA.cbWndExtra == sizeof(LONG_PTR), "got %d\n", cliA.cbWndExtra);
    ok(cliA.lpszMenuName == 0, "got %s\n", cliA.lpszMenuName);

    DestroyWindow(hwnd);

    /* set extra bytes */
    hwnd = pSHCreateWorkerWindowA(0, NULL, 0, 0, 0, 0xdeadbeef);
    ok(hwnd != 0, "expected window\n");

    GetClassNameA(hwnd, classA, 20);
    ok(lstrcmpA(classA, "WorkerA") == 0, "expected WorkerA class, got %s\n", classA);

    ret = GetWindowLongPtrA(hwnd, 0);
    ok(ret == 0xdeadbeef, "got %ld\n", ret);

    /* test exstyle */
    ret = GetWindowLongA(hwnd, GWL_EXSTYLE);
    ok(ret == WS_EX_WINDOWEDGE ||
       ret == (WS_EX_WINDOWEDGE|WS_EX_LAYOUTRTL) /* systems with RTL locale */, "0x%08lx\n", ret);

    DestroyWindow(hwnd);

    hwnd = pSHCreateWorkerWindowA(0, NULL, WS_EX_TOOLWINDOW, 0, 0, 0);
    ret = GetWindowLongA(hwnd, GWL_EXSTYLE);
    ok(ret == (WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW) ||
       ret == (WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW|WS_EX_LAYOUTRTL) /* systems with RTL locale */, "0x%08lx\n", ret);
    DestroyWindow(hwnd);
}