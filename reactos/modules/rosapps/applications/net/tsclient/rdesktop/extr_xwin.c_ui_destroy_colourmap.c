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
struct TYPE_3__ {int /*<<< orphan*/  display; int /*<<< orphan*/  owncolmap; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  scalar_t__ HCOLOURMAP ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void
ui_destroy_colourmap(RDPCLIENT * This, HCOLOURMAP map)
{
	if (!This->owncolmap)
		xfree(map);
	else
		XFreeColormap(This->display, (Colormap) map);
}