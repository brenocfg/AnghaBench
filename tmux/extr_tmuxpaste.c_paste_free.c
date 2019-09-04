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
struct paste_buffer {struct paste_buffer* name; struct paste_buffer* data; scalar_t__ automatic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  free (struct paste_buffer*) ; 
 int /*<<< orphan*/  paste_by_name ; 
 int /*<<< orphan*/  paste_by_time ; 
 int /*<<< orphan*/  paste_name_tree ; 
 int /*<<< orphan*/  paste_num_automatic ; 
 int /*<<< orphan*/  paste_time_tree ; 

void
paste_free(struct paste_buffer *pb)
{
	RB_REMOVE(paste_name_tree, &paste_by_name, pb);
	RB_REMOVE(paste_time_tree, &paste_by_time, pb);
	if (pb->automatic)
		paste_num_automatic--;

	free(pb->data);
	free(pb->name);
	free(pb);
}