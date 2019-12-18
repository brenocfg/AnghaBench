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
struct TYPE_4__ {int num_separations; } ;
typedef  TYPE_1__ fz_separations ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_SEPARATION_SPOT ; 
 scalar_t__ sep_state (TYPE_1__ const*,int) ; 

int fz_count_active_separations(fz_context *ctx, const fz_separations *sep)
{
	int i, n, c;

	if (!sep)
		return 0;
	n = sep->num_separations;
	c = 0;
	for (i = 0; i < n; i++)
		if (sep_state(sep, i) == FZ_SEPARATION_SPOT)
			c++;
	return c;
}