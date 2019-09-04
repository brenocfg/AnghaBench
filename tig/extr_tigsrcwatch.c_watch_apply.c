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
struct watch {int dummy; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_EVENT_LOAD ; 
 int /*<<< orphan*/  watch_apply_changes (struct watch*,int /*<<< orphan*/ ,int) ; 

void
watch_apply(struct watch *source, enum watch_trigger changed)
{
	watch_apply_changes(source, WATCH_EVENT_LOAD, changed);
}