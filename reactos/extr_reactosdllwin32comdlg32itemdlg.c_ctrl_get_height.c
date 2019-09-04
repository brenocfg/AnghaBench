#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wrapper_hwnd; } ;
typedef  TYPE_1__ customctrl ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_2__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static UINT ctrl_get_height(customctrl *ctrl) {
    RECT rc;
    GetWindowRect(ctrl->wrapper_hwnd, &rc);
    return rc.bottom - rc.top;
}