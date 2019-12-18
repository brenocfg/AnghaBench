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
struct frame_index {size_t fill; scalar_t__ data; scalar_t__ size; int /*<<< orphan*/  next; int /*<<< orphan*/  step; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug3 (char*,unsigned long,unsigned long,void*) ; 
 int /*<<< orphan*/  fi_next (struct frame_index*) ; 
 int fi_resize (struct frame_index*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 

int fi_set(struct frame_index *fi, off_t *offsets, off_t step, size_t fill)
{
	if(fi_resize(fi, fill) == -1) return -1;
	fi->step = step;
	if(offsets != NULL)
	{
		memcpy(fi->data, offsets, fill*sizeof(off_t));
		fi->fill = fill;
	}
	else
	{
		/* allocation only, no entries in index yet */
		fi->fill = 0;
	}
	fi->next = fi_next(fi);
	debug3("set new index of fill %lu, size %lu at %p",
	(unsigned long)fi->fill, (unsigned long)fi->size, (void*)fi->data);
	return 0;
}