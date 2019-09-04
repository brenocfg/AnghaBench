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
struct shrmap {unsigned int mask; int roslots; int /*<<< orphan*/  lock; struct shrmap_slot* readonly; struct shrmap_slot* readwrite; } ;
typedef  int /*<<< orphan*/  lu_byte ;
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 struct shrmap SSM ; 
 int /*<<< orphan*/ * find_string (int /*<<< orphan*/ *,struct shrmap_slot*,unsigned int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_runlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TString *
query_string(TString *t, unsigned int h, const char *str, lu_byte l) {
	struct shrmap * s = &SSM;
	TString *ts = NULL;
	rwlock_rlock(&s->lock);
		struct shrmap_slot *slot = &s->readwrite[h & s->mask];
		rwlock_rlock(&slot->lock);
			ts = find_string(t, slot, h, str, l);
		rwlock_runlock(&slot->lock);
		if (ts == NULL && s->readonly != NULL) {
			int mask = s->roslots - 1;
			slot = &s->readonly[h & mask];
			rwlock_rlock(&slot->lock);
				ts = find_string(t, slot, h, str, l);
			rwlock_runlock(&slot->lock);
		}
	rwlock_runlock(&s->lock);
	return ts;
}