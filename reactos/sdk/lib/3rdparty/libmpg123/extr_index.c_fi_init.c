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
struct frame_index {int step; int /*<<< orphan*/  next; scalar_t__ grow_size; scalar_t__ size; scalar_t__ fill; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fi_next (struct frame_index*) ; 

void fi_init(struct frame_index *fi)
{
	fi->data = NULL;
	fi->step = 1;
	fi->fill = 0;
	fi->size = 0;
	fi->grow_size = 0;
	fi->next = fi_next(fi);
}