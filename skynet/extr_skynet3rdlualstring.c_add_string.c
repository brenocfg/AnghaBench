#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shrmap_slot {int /*<<< orphan*/  lock; struct TString* str; } ;
struct shrmap {unsigned int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  total; struct shrmap_slot* readwrite; } ;
struct TYPE_2__ {struct TString* hnext; } ;
struct TString {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  lu_byte ;
typedef  struct TString TString ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_INC (int /*<<< orphan*/ *) ; 
 struct shrmap SSM ; 
 int /*<<< orphan*/  free (struct TString*) ; 
 struct TString* new_string (unsigned int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 
 struct TString* shrstr_exist (struct shrmap*,unsigned int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TString *
add_string(unsigned int h, const char *str, lu_byte l) {
	struct shrmap * s = &SSM;
	TString * tmp = new_string(h, str, l);
	rwlock_rlock(&s->lock);
		struct TString *ts = shrstr_exist(s, h, str, l);
		if (ts) {
			// string is create by other thread, so free tmp
			free(tmp);
		} else {
			struct shrmap_slot *slot = &s->readwrite[h & s->mask];
			ts = tmp;
			ts->u.hnext = slot->str;
			slot->str = ts;
			rwlock_wunlock(&slot->lock);
			ATOM_INC(&SSM.total);
		}
	rwlock_runlock(&s->lock);
	return ts;
}