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
typedef  int LRESULT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TB_GETBUTTONSIZE ; 
 int /*<<< orphan*/  TB_SETBUTTONSIZE ; 
 int /*<<< orphan*/  TOOLBARCLASSNAMEW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void TestSetButtonSize()
{
    HWND hwnd;
    LRESULT bsize;

    hwnd = CreateWindowExW(0, TOOLBARCLASSNAMEW, L"Test", 0, 0, 0, 0, 0, 0, 0, 0, NULL);
    ok(hwnd != NULL, "CreateWindowEx failed\n");

    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x160017, "Expected 0x160017 got %lx\n", bsize);

    SendMessageW(hwnd, TB_SETBUTTONSIZE, 0, MAKELONG(0, 0));
    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x160018, "Expected 0x160018 got %lx\n", bsize);

    SendMessageW(hwnd, TB_SETBUTTONSIZE, 0, 0x10001);
    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x160017, "Expected 0x160017 got %lx\n", bsize);

    SendMessageW(hwnd, TB_SETBUTTONSIZE, 0, 0x100001);
    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x160017, "Expected 0x160017 got %lx\n", bsize);

    SendMessageW(hwnd, TB_SETBUTTONSIZE, 0, 0x160017);
    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x160017, "Expected 0x160017 got %lx\n", bsize);

    SendMessageW(hwnd, TB_SETBUTTONSIZE, 0, 0x170017);
    bsize = SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    ok(bsize == 0x170017, "Expected 0x170017 got %lx\n", bsize);

    DestroyWindow(hwnd);
}