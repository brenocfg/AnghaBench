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
struct TYPE_3__ {char* href; struct TYPE_3__* up; } ;
typedef  TYPE_1__ fz_html_box ;

/* Variables and functions */

__attribute__((used)) static const char *box_href(fz_html_box *box)
{
	while (box)
	{
		const char *href = box->href;
		if (href)
			return href;
		box = box->up;
	}
	return NULL;
}