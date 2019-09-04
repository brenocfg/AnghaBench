#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shrmap_slot {int /*<<< orphan*/  lock; TYPE_2__* str; } ;
struct shrmap {int mask; struct shrmap_slot* readwrite; struct shrmap_slot* readonly; } ;
struct TYPE_3__ {TYPE_2__* hnext; } ;
struct TYPE_4__ {int hash; TYPE_1__ u; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shrstr_rehash(struct shrmap *s, int slotid) {
	struct shrmap_slot *slot = &s->readonly[slotid];
	rwlock_wlock(&slot->lock);
		TString *str = slot->str;
		while (str) {
			TString * next = str->u.hnext;
			int newslotid = str->hash & s->mask;
			struct shrmap_slot *newslot = &s->readwrite[newslotid];
			rwlock_wlock(&newslot->lock);
				str->u.hnext = newslot->str;
				newslot->str = str;
			rwlock_wunlock(&newslot->lock);
			str = next;
		}

		slot->str = NULL;
	rwlock_wunlock(&slot->lock);
}