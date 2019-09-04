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
struct TYPE_2__ {struct shrmap_slot* hnext; } ;
struct shrmap_slot {TYPE_1__ u; struct shrmap_slot* str; } ;
typedef  struct shrmap_slot TString ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct shrmap_slot*) ; 

__attribute__((used)) static void
shrstr_deletepage(struct shrmap_slot *s, int sz) {
	if (s) {
		int i;
		for (i=0;i<sz;i++) {
			TString *str = s[i].str;
			while (str) {
				TString * next = str->u.hnext;
				free(str);
				str = next;
			}
		}
		free(s);
	}
}