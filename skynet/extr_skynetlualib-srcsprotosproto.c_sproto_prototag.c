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
struct sproto {int protocol_n; TYPE_1__* proto; } ;
struct TYPE_2__ {int tag; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
sproto_prototag(const struct sproto *sp, const char * name) {
	int i;
	for (i=0;i<sp->protocol_n;i++) {
		if (strcmp(name, sp->proto[i].name) == 0) {
			return sp->proto[i].tag;
		}
	}
	return -1;
}