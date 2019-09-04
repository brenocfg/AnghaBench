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
struct winlink {int dummy; } ;
struct session {int /*<<< orphan*/  windows; } ;

/* Variables and functions */
 int session_set_current (struct session*,struct winlink*) ; 
 struct winlink* winlink_find_by_index (int /*<<< orphan*/ *,int) ; 

int
session_select(struct session *s, int idx)
{
	struct winlink	*wl;

	wl = winlink_find_by_index(&s->windows, idx);
	return (session_set_current(s, wl));
}