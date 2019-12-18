#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (unsigned char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int get_current_desktop (TYPE_1__*) ; 
 scalar_t__ get_property_value (TYPE_1__*,int /*<<< orphan*/ ,char*,int const,unsigned long*,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
get_current_workarea(RDPCLIENT * This, uint32 * x, uint32 * y, uint32 * width, uint32 * height)
{
	int current_desktop;
	unsigned long nitems_return;
	unsigned char *prop_return;
	uint32 *return_words;
	const uint32 net_workarea_x_offset = 0;
	const uint32 net_workarea_y_offset = 1;
	const uint32 net_workarea_width_offset = 2;
	const uint32 net_workarea_height_offset = 3;
	const uint32 max_prop_length = 32 * 4;	/* Max 32 desktops */

	if (get_property_value
	    (This, DefaultRootWindow(This->display), "_NET_WORKAREA", max_prop_length, &nitems_return,
	     &prop_return, 0) < 0)
		return (-1);

	if (nitems_return % 4)
	{
		fprintf(stderr, "_NET_WORKAREA has odd length\n");
		return (-1);
	}

	current_desktop = get_current_desktop(This);

	if (current_desktop < 0)
		return -1;

	return_words = (uint32 *) prop_return;

	*x = return_words[current_desktop * 4 + net_workarea_x_offset];
	*y = return_words[current_desktop * 4 + net_workarea_y_offset];
	*width = return_words[current_desktop * 4 + net_workarea_width_offset];
	*height = return_words[current_desktop * 4 + net_workarea_height_offset];

	XFree(prop_return);

	return (0);

}