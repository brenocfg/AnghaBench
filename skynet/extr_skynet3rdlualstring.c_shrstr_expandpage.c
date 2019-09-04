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
struct shrmap {int mask; int /*<<< orphan*/  lock; struct shrmap_slot* readonly; } ;

/* Variables and functions */
 struct shrmap SSM ; 
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 
 int shrstr_allocpage (struct shrmap*,int,int,struct shrmap_slot*) ; 
 int /*<<< orphan*/  shrstr_deletepage (struct shrmap_slot*,int) ; 
 struct shrmap_slot* shrstr_newpage (int) ; 
 int /*<<< orphan*/  shrstr_rehash (struct shrmap*,int) ; 

__attribute__((used)) static void
shrstr_expandpage(int cap) {
	struct shrmap * s = &SSM;
	if (s->readonly)
		return;
	int osz = s->mask + 1;
	int sz = osz * 2;
	while (sz < cap) {
		// overflow check
		if (sz <= 0)
			return;
		sz = sz * 2;
	}
	struct shrmap_slot * newpage = shrstr_newpage(sz);
	if (newpage == NULL)
		return;
	rwlock_wlock(&s->lock);
	int succ = shrstr_allocpage(s, osz, sz, newpage);
	rwlock_wunlock(&s->lock);
	if (!succ) {
		shrstr_deletepage(newpage, sz);
		return;
	}
	int i;
	for (i=0;i<osz;i++) {
		shrstr_rehash(s, i);
	}
	rwlock_wlock(&s->lock);
		struct shrmap_slot * oldpage = s->readonly;
		s->readonly = NULL;
	rwlock_wunlock(&s->lock);
	shrstr_deletepage(oldpage, osz);
}