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
struct watch {int state; int changed; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;

/* Variables and functions */
 int WATCH_INDEX ; 
 int WATCH_NONE ; 
 int watch_trigger_unmask (int,int) ; 

bool
watch_dirty(struct watch *watch)
{
	enum watch_trigger old_index = watch->state & WATCH_INDEX;
	enum watch_trigger new_index = watch->changed & WATCH_INDEX;
	enum watch_trigger index = watch_trigger_unmask(new_index, old_index);
	enum watch_trigger other = watch_trigger_unmask(watch->changed, WATCH_INDEX);
	bool dirty = !!(index | other);

	watch->changed = WATCH_NONE;
	return dirty;
}