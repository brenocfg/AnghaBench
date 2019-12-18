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
struct TYPE_2__ {scalar_t__ rn_rrl; } ;
typedef  TYPE_1__ rrw_node_t ;

/* Variables and functions */
 scalar_t__ curthread ; 
 int /*<<< orphan*/  panic (char*,void*,void*) ; 

void
rrw_tsd_destroy(void *arg)
{
	rrw_node_t *rn = arg;
	if (rn != NULL) {
		panic("thread %p terminating with rrw lock %p held",
		    (void *)curthread, (void *)rn->rn_rrl);
	}
}