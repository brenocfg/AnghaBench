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
struct slotinfo {int /*<<< orphan*/  size; int /*<<< orphan*/  len; } ;
struct shrmap_slot {int /*<<< orphan*/  lock; TYPE_2__* str; } ;
struct TYPE_3__ {TYPE_2__* hnext; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  shrlen; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct slotinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_runlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sizelstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getslot(struct shrmap_slot *s, struct slotinfo *info) {
	memset(info, 0, sizeof(*info));
	rwlock_rlock(&s->lock);
	TString *ts = s->str;
	while (ts) {
		++info->len;
		info->size += sizelstring(ts->shrlen);
		ts = ts->u.hnext;
	}
	rwlock_runlock(&s->lock);
}