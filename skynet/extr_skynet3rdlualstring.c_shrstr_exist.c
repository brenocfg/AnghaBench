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
struct shrmap_slot {int /*<<< orphan*/  lock; } ;
struct shrmap {int roslots; unsigned int mask; struct shrmap_slot* readwrite; struct shrmap_slot* readonly; } ;
typedef  int /*<<< orphan*/  lu_byte ;
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 int /*<<< orphan*/ * find_string (int /*<<< orphan*/ *,struct shrmap_slot*,unsigned int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TString *
shrstr_exist(struct shrmap * s, unsigned int h, const char *str, lu_byte l) {
	TString *found;
	if (s->readonly) {
		unsigned int mask = s->roslots - 1;
		struct shrmap_slot *slot = &s->readonly[h & mask];
		rwlock_rlock(&slot->lock);
			found = find_string(NULL, slot, h, str, l);
		rwlock_runlock(&slot->lock);
		if (found)
			return found;
	}
	struct shrmap_slot *slot = &s->readwrite[h & s->mask];
	rwlock_wlock(&slot->lock);
	found = find_string(NULL, slot, h, str, l);
	if (found) {
		rwlock_wunlock(&slot->lock);
		return found;
	}
	// not found, lock slot and return.
	return NULL;
}