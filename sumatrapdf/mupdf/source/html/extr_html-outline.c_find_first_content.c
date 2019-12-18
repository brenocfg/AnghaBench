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
typedef  int /*<<< orphan*/  fz_html_flow ;
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* down; int /*<<< orphan*/ * flow_head; } ;
typedef  TYPE_1__ fz_html_box ;

/* Variables and functions */
 scalar_t__ BOX_FLOW ; 

__attribute__((used)) static fz_html_flow *
find_first_content(fz_html_box *box)
{
	while (box)
	{
		if (box->type == BOX_FLOW)
			return box->flow_head;
		box = box->down;
	}
	return NULL;
}