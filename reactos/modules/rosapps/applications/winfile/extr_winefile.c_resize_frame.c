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
struct TYPE_3__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  resize_frame_rect (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void resize_frame(HWND hwnd, int cx, int cy)
{
	RECT rect;

	rect.left   = 0;
	rect.top    = 0;
	rect.right  = cx;
	rect.bottom = cy;

	resize_frame_rect(hwnd, &rect);
}