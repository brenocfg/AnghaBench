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
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int MAX_DEPTH ; 
 float fz_abs (float) ; 
 float fz_max (float,float) ; 
 int /*<<< orphan*/  line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,float,float,float) ; 

__attribute__((used)) static void
quad(fz_context *ctx, fz_rasterizer *rast, fz_matrix ctm, float flatness,
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
	if (dmax < flatness || depth >= MAX_DEPTH)
	{
		line(ctx, rast, ctm, xa, ya, xc, yc);
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

	quad(ctx, rast, ctm, flatness, xa, ya, xab, yab, xabc, yabc, depth + 1);
	quad(ctx, rast, ctm, flatness, xabc, yabc, xbc, ybc, xc, yc, depth + 1);
}