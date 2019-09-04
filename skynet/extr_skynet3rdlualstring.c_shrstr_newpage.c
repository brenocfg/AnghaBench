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
struct shrmap_slot {int /*<<< orphan*/ * str; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct shrmap_slot *
shrstr_newpage(int sz) {
	int i;
	struct shrmap_slot * s = (struct shrmap_slot *)malloc(sz * sizeof(*s));
	if (s == NULL)
		return NULL;
	for (i=0;i<sz;i++) {
		rwlock_init(&s[i].lock);
		s[i].str = NULL;
	}
	return s;
}