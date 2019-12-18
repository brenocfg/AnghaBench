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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUSCLASSNAMEA ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static HWND create_status_control(DWORD style, DWORD exstyle)
{
    HWND hWndStatus;

    /* make the control */
    hWndStatus = CreateWindowExA(exstyle, STATUSCLASSNAMEA, NULL, style,
        /* placement */
        0, 0, 300, 20,
        /* parent, etc */
        NULL, NULL, hinst, NULL);
    ok(hWndStatus != NULL, "failed to create status wnd\n");
    return hWndStatus;
}