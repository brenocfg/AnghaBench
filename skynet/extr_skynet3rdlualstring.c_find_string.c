#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct shrmap_slot {TYPE_2__* str; } ;
typedef  scalar_t__ lu_byte ;
struct TYPE_6__ {TYPE_2__* hnext; } ;
struct TYPE_7__ {unsigned int hash; scalar_t__ shrlen; TYPE_1__ u; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static TString *
find_string(TString *t, struct shrmap_slot * slot, unsigned int h, const char *str, lu_byte l) {
	TString *ts = slot->str;
	if (t) {
		while (ts) {
			if (ts == t)
				break;
			ts = ts->u.hnext;
		}
	} else {
		while (ts) {
			if (ts->hash == h &&
				ts->shrlen == l &&
				memcmp(str, ts+1, l) == 0) {
				break;
			}
			ts = ts->u.hnext;
		}
	}
	return ts;
}