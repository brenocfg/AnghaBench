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
struct sctx {float flatness; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int MAX_DEPTH ; 
 float fz_abs (float) ; 
 int /*<<< orphan*/  fz_dash_lineto (int /*<<< orphan*/ *,struct sctx*,float,float,int) ; 
 float fz_max (float,float) ; 

__attribute__((used)) static void
fz_dash_quad(fz_context *ctx, struct sctx *s,
	float xa, float ya,
	float xb, float yb,
	float xc, float yc, int depth)
{
	float dmax;
	float xab, yab;
	float xbc, ybc;
	float xabc, yabc;

	/* termination check */
	dmax = fz_abs(xa - xb);
	dmax = fz_max(dmax, fz_abs(ya - yb));
	dmax = fz_max(dmax, fz_abs(xc - xb));
	dmax = fz_max(dmax, fz_abs(yc - yb));
	if (dmax < s->flatness || depth >= MAX_DEPTH)
	{
		fz_dash_lineto(ctx, s, xc, yc, 1);
		return;
	}

	xab = xa + xb;
	yab = ya + yb;
	xbc = xb + xc;
	ybc = yb + yc;

	xabc = xab + xbc;
	yabc = yab + ybc;

	xab *= 0.5f; yab *= 0.5f;
	xbc *= 0.5f; ybc *= 0.5f;

	xabc *= 0.25f; yabc *= 0.25f;

	fz_dash_quad(ctx, s, xa, ya, xab, yab, xabc, yabc, depth + 1);
	fz_dash_quad(ctx, s, xabc, yabc, xbc, ybc, xc, yc, depth + 1);
}