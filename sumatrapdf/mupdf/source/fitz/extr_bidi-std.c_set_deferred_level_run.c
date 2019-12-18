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
typedef  int /*<<< orphan*/  fz_bidi_level ;

/* Variables and functions */

__attribute__((used)) static
void set_deferred_level_run(fz_bidi_level *pval, size_t cval, size_t iStart, fz_bidi_level nval)
{
	size_t i;

	for (i = iStart; i > iStart - cval; )
	{
		pval[--i] = nval;
	}
}