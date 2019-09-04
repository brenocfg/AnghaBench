#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  wnd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * colmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; TYPE_1__ xwin; int /*<<< orphan*/  owncolmap; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  scalar_t__ HCOLOURMAP ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetWindowColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* sw ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
ui_set_colourmap(RDPCLIENT * This, HCOLOURMAP map)
{
	if (!This->owncolmap)
	{
		if (This->xwin.colmap)
			xfree(This->xwin.colmap);

		This->xwin.colmap = (uint32 *) map;
	}
	else
	{
		XSetWindowColormap(This->display, This->wnd, (Colormap) map);
		ON_ALL_SEAMLESS_WINDOWS(XSetWindowColormap, (This->display, sw->wnd, (Colormap) map));
	}
}