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
struct window {scalar_t__ references; } ;
struct session_group {int dummy; } ;
struct session {int dummy; } ;

/* Variables and functions */
 struct session_group* session_group_contains (struct session*) ; 
 scalar_t__ session_group_count (struct session_group*) ; 

int
session_is_linked(struct session *s, struct window *w)
{
	struct session_group	*sg;

	if ((sg = session_group_contains(s)) != NULL)
		return (w->references != session_group_count(sg));
	return (w->references != 1);
}