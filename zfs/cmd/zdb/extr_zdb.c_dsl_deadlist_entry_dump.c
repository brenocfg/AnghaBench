#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_5__ {scalar_t__ bpo_object; } ;
struct TYPE_4__ {TYPE_2__ dle_bpobj; scalar_t__ dle_mintxg; } ;
typedef  TYPE_1__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_full_bpobj (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_deadlist_entry_dump(void *arg, dsl_deadlist_entry_t *dle)
{
	ASSERT(arg == NULL);
	if (dump_opt['d'] >= 5) {
		char buf[128];
		(void) snprintf(buf, sizeof (buf),
		    "mintxg %llu -> obj %llu",
		    (longlong_t)dle->dle_mintxg,
		    (longlong_t)dle->dle_bpobj.bpo_object);

		dump_full_bpobj(&dle->dle_bpobj, buf, 0);
	} else {
		(void) printf("mintxg %llu -> obj %llu\n",
		    (longlong_t)dle->dle_mintxg,
		    (longlong_t)dle->dle_bpobj.bpo_object);
	}
	return (0);
}