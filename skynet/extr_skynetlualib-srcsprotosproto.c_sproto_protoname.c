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
struct sproto {int dummy; } ;
struct protocol {char const* name; } ;

/* Variables and functions */
 struct protocol* query_proto (struct sproto const*,int) ; 

const char *
sproto_protoname(const struct sproto *sp, int proto) {
	struct protocol * p = query_proto(sp, proto);
	if (p) {
		return p->name;
	}
	return NULL;
}