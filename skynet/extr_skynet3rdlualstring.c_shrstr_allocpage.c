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
struct shrmap_slot {int dummy; } ;
struct shrmap {int mask; int roslots; struct shrmap_slot* readwrite; struct shrmap_slot* readonly; } ;

/* Variables and functions */

__attribute__((used)) static int
shrstr_allocpage(struct shrmap * s, int osz, int sz, struct shrmap_slot * newpage) {
	if (s->readonly != NULL)
		return 0;
	if ((s->mask + 1) != osz)
		return 0;
	s->readonly = s->readwrite;
	s->readwrite = newpage;
	s->roslots = s->mask + 1;
	s->mask = sz - 1;

	return 1;
}