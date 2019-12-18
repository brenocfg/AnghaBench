#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; int alpha; int s; int /*<<< orphan*/  seps; int /*<<< orphan*/ * colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 char* fz_colorspace_colorant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_colorspace_is_subtractive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fz_separation_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_set_overprint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static fz_overprint *
set_op_from_spaces(fz_context *ctx, fz_overprint *op, const fz_pixmap *dest, fz_colorspace *src, int opm)
{
	int dn, sn, i, j, dc;

	if (!op)
		return NULL;

	if (!fz_colorspace_is_subtractive(ctx, src) || !fz_colorspace_is_subtractive(ctx, dest->colorspace))
		return NULL;

	sn = fz_colorspace_n(ctx, src);
	dn = dest->n - dest->alpha;
	dc = dn - dest->s;

	/* If a source colorant is not mentioned in the destination
	 * colorants (either process or spots), then it will be mapped
	 * to process colorants. In this case, the process colorants
	 * can never be protected.
	 */
	for (j = 0; j < sn; j++)
	{
		/* Run through the colorants looking for one that isn't mentioned.
		 * i.e. continue if we we find one, break if not. */
		const char *sname = fz_colorspace_colorant(ctx, src, j);
		if (!sname)
			break;
		if (!strcmp(sname, "All") || !strcmp(sname, "None"))
			continue;
		for (i = 0; i < dc; i++)
		{
			const char *name = fz_colorspace_colorant(ctx, dest->colorspace, i);
			if (!name)
				continue;
			if (!strcmp(name, sname))
				break;
		}
		if (i != dc)
			continue;
		for (; i < dn; i++)
		{
			const char *name = fz_separation_name(ctx, dest->seps, i - dc);
			if (!name)
				continue;
			if (!strcmp(name, sname))
				break;
		}
		if (i == dn)
		{
			/* This source colorant wasn't mentioned */
			break;
		}
	}
	if (j == sn)
	{
		/* We did not find any source colorants that weren't mentioned, so
		 * process colorants might not be touched... */
		for (i = 0; i < dc; i++)
		{
			const char *name = fz_colorspace_colorant(ctx, dest->colorspace, i);

			for (j = 0; j < sn; j++)
			{
				const char *sname = fz_colorspace_colorant(ctx, src, j);
				if (!name || !sname)
					continue;
				if (!strcmp(name, sname))
					break;
				if (!strcmp(sname, "All"))
					break;
			}
			if (j == sn)
				fz_set_overprint(op, i);
		}
	}
	for (i = dc; i < dn; i++)
	{
		const char *name = fz_separation_name(ctx, dest->seps, i - dc);

		for (j = 0; j < sn; j++)
		{
			const char *sname = fz_colorspace_colorant(ctx, src, j);
			if (!name || !sname)
				continue;
			if (!strcmp(name, sname))
				break;
			if (!strcmp(sname, "All"))
				break;
		}
		if (j == sn)
			fz_set_overprint(op, i);
	}

	return op;
}