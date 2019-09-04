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
struct sproto_type {int /*<<< orphan*/  name; } ;
struct sproto {int type_n; struct sproto_type* type; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

struct sproto_type *
sproto_type(const struct sproto *sp, const char * type_name) {
	int i;
	for (i=0;i<sp->type_n;i++) {
		if (strcmp(type_name, sp->type[i].name) == 0) {
			return &sp->type[i];
		}
	}
	return NULL;
}