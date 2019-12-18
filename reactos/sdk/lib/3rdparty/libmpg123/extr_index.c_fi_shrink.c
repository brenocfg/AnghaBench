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
struct frame_index {int fill; int step; int /*<<< orphan*/  next; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug2 (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  fi_next (struct frame_index*) ; 

__attribute__((used)) static void fi_shrink(struct frame_index *fi)
{
	if(fi->fill < 2) return; /* Won't shrink below 1. */
	else
	{ /* Double the step, half the fill. Should work as well for fill%2 = 1 */
		size_t c;
		debug2("shrink index with fill %lu and step %lu", (unsigned long)fi->fill, (unsigned long)fi->step);
		fi->step *= 2;
		fi->fill /= 2;
		/* Move the data down. */
		for(c = 0; c < fi->fill; ++c)
		fi->data[c] = fi->data[2*c];
	}

	fi->next = fi_next(fi);
}