#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int alen; TYPE_1__** active; } ;
typedef  TYPE_2__ fz_gel ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_span_aa (int /*<<< orphan*/ *,TYPE_2__*,int*,int,int,int,int) ; 

__attribute__((used)) static inline void
even_odd_aa(fz_context *ctx, fz_gel *gel, int *list, int xofs, int h)
{
	int even = 0;
	int x = 0;
	int i;

	for (i = 0; i < gel->alen; i++)
	{
		if (!even)
			x = gel->active[i]->x;
		else
			add_span_aa(ctx, gel, list, x, gel->active[i]->x, xofs, h);
		even = !even;
	}
}