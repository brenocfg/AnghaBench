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
typedef  int /*<<< orphan*/  Window ;
struct TYPE_3__ {int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XQueryPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,unsigned int*) ; 

unsigned int
read_keyboard_state(RDPCLIENT * This)
{
#ifdef RDP2VNC
	return 0;
#else
	unsigned int state;
	Window wdummy;
	int dummy;

	XQueryPointer(This->display, This->wnd, &wdummy, &wdummy, &dummy, &dummy, &dummy, &dummy, &state);
	return state;
#endif
}