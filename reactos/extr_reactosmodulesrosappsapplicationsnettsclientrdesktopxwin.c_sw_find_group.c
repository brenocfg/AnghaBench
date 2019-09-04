#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* group; struct TYPE_9__* next; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_10__ {unsigned long id; scalar_t__ refcnt; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_3__ seamless_group ;
typedef  int /*<<< orphan*/  XSetWindowAttributes ;
struct TYPE_8__ {int /*<<< orphan*/  screen; TYPE_2__* seamless_windows; } ;
struct TYPE_11__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_4__ RDPCLIENT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyFromParent ; 
 int /*<<< orphan*/  RootWindowOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* xmalloc (int) ; 

__attribute__((used)) static seamless_group *
sw_find_group(RDPCLIENT * This, unsigned long id, BOOL dont_create)
{
	seamless_window *sw;
	seamless_group *sg;
	XSetWindowAttributes attribs;

	for (sw = This->xwin.seamless_windows; sw; sw = sw->next)
	{
		if (sw->group->id == id)
			return sw->group;
	}

	if (dont_create)
		return NULL;

	sg = xmalloc(sizeof(seamless_group));

	sg->wnd =
		XCreateWindow(This->display, RootWindowOfScreen(This->xwin.screen), -1, -1, 1, 1, 0,
			      CopyFromParent, CopyFromParent, CopyFromParent, 0, &attribs);

	sg->id = id;
	sg->refcnt = 0;

	return sg;
}