#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/  lpfnWndProc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefWindowProcA ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 

__attribute__((used)) static HWND create_window(void)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = DefWindowProcA;
    wc.lpszClassName = "d3d9_test_wc";
    RegisterClassA(&wc);

    return CreateWindowA("d3d9_test_wc", "d3d9_test", 0, 0, 0, 0, 0, 0, 0, 0, 0);
}