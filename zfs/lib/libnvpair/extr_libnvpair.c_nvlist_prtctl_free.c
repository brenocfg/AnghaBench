#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nvlist_prtctl_t ;
struct TYPE_4__ {struct TYPE_4__* nvprt_custops; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
nvlist_prtctl_free(nvlist_prtctl_t pctl)
{
	if (pctl != NULL) {
		free(pctl->nvprt_custops);
		free(pctl);
	}
}