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
struct TYPE_4__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ trace_info ;
struct TYPE_5__ {scalar_t__ size; } ;
typedef  TYPE_2__ trace_header ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
trace_free(void *arg, void *p_)
{
	trace_info *info = (trace_info *) arg;
	trace_header *p = (trace_header *)p_;

	if (p == NULL)
		return;
	info->current -= p[-1].size;
	free(&p[-1]);
}