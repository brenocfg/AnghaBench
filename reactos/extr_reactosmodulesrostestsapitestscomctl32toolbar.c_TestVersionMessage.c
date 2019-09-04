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
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_GETVERSION ; 
 int /*<<< orphan*/  CCM_SETVERSION ; 
 int /*<<< orphan*/ * CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLBARCLASSNAMEW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void TestVersionMessage()
{
    HWND hwnd;
    int version;

    hwnd = CreateWindowExW(0, TOOLBARCLASSNAMEW, L"Test", 0, 0, 0, 0, 0, 0, 0, 0, NULL);
    ok(hwnd != NULL, "CreateWindowEx failed\n");

    version = SendMessageW(hwnd, CCM_GETVERSION, 0, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_SETVERSION, 5, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_GETVERSION, 0, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_SETVERSION, 7, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_GETVERSION, 0, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_SETVERSION, 4, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    version = SendMessageW(hwnd, CCM_GETVERSION, 0, 0);
    ok(version == 6, "Got %d, expected 6\n", version);

    DestroyWindow(hwnd);
}