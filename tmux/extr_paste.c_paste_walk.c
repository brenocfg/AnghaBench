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
struct paste_buffer {int dummy; } ;

/* Variables and functions */
 struct paste_buffer* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct paste_buffer* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  paste_by_time ; 
 int /*<<< orphan*/  paste_time_tree ; 

struct paste_buffer *
paste_walk(struct paste_buffer *pb)
{
	if (pb == NULL)
		return (RB_MIN(paste_time_tree, &paste_by_time));
	return (RB_NEXT(paste_time_tree, &paste_by_time, pb));
}