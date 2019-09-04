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
struct vatpit {TYPE_1__* channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct vatpit*) ; 

void
vatpit_cleanup(struct vatpit *vatpit)
{
	int i;

	for (i = 0; i < 3; i++)
		callout_drain(&vatpit->channel[i].callout);

	free(vatpit);
}