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
struct frame_index {size_t size; size_t fill; int /*<<< orphan*/ * data; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug2 (char*,unsigned long,void*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fi_next (struct frame_index*) ; 
 int /*<<< orphan*/  fi_shrink (struct frame_index*) ; 
 int /*<<< orphan*/ * safe_realloc (int /*<<< orphan*/ *,size_t) ; 

int fi_resize(struct frame_index *fi, size_t newsize)
{
	off_t *newdata = NULL;
	if(newsize == fi->size) return 0;

	if(newsize > 0 && newsize < fi->size)
	{ /* When we reduce buffer size a bit, shrink stuff. */
		while(fi->fill > newsize){ fi_shrink(fi); }
	}

	newdata = safe_realloc(fi->data, newsize*sizeof(off_t));
	if(newsize == 0 || newdata != NULL)
	{
		fi->data = newdata;
		fi->size = newsize;
		if(fi->fill > fi->size) fi->fill = fi->size;

		fi->next = fi_next(fi);
		debug2("new index of size %lu at %p", (unsigned long)fi->size, (void*)fi->data);
		return 0;
	}
	else
	{
		error("failed to resize index!");
		return -1;
	}
}