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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTextA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPM_SETADDRESS ; 
 int /*<<< orphan*/  MAKEIPADDRESS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ipaddress_control () ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_get_set_text(void)
{
    HWND hwnd;
    CHAR ip[16];
    INT r;

    hwnd = create_ipaddress_control();
    if (!hwnd)
    {
        win_skip("IPAddress control not implemented\n");
        return;
    }

    /* check text just after creation */
    r = GetWindowTextA(hwnd, ip, ARRAY_SIZE(ip));
    expect(7, r);
    ok(strcmp(ip, "0.0.0.0") == 0, "Expected null IP address, got %s\n", ip);

    SendMessageA(hwnd, IPM_SETADDRESS, 0, MAKEIPADDRESS(127, 0, 0, 1));
    r = GetWindowTextA(hwnd, ip, ARRAY_SIZE(ip));
    expect(9, r);
    ok(strcmp(ip, "127.0.0.1") == 0, "Expected 127.0.0.1, got %s\n", ip);

    DestroyWindow(hwnd);
}