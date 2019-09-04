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
struct sproto_type {int dummy; } ;
struct sproto {int dummy; } ;
struct protocol {struct sproto_type** p; } ;

/* Variables and functions */
 struct protocol* query_proto (struct sproto const*,int) ; 

struct sproto_type *
sproto_protoquery(const struct sproto *sp, int proto, int what) {
	struct protocol * p;
	if (what <0 || what >1) {
		return NULL;
	}
	p = query_proto(sp, proto);
	if (p) {
		return p->p[what];
	}
	return NULL;
}