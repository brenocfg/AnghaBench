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
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WS_OVERLAPPED ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_invisible_create(void)
{
    HWND hwnd_owndc = CreateWindowA("owndc_class", NULL, WS_OVERLAPPED,
                                    0, 200, 100, 100,
                                    0, 0, GetModuleHandleA(0), NULL );
    HDC dc1, dc2;

    dc1 = GetDC(hwnd_owndc);
    dc2 = GetDC(hwnd_owndc);

    ok(dc1 == dc2, "expected owndc dcs to match\n");

    ReleaseDC(hwnd_owndc, dc2);
    ReleaseDC(hwnd_owndc, dc1);
    DestroyWindow(hwnd_owndc);
}