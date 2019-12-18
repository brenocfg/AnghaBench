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
typedef  int /*<<< orphan*/  fz_edgebuffer ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fixed ;

/* Variables and functions */
 int /*<<< orphan*/  float2fixed (float) ; 
 int /*<<< orphan*/  mark_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fz_insert_edgebuffer(fz_context *ctx, fz_rasterizer *ras, float fsx, float fsy, float fex, float fey, int rev)
{
	fz_edgebuffer *eb = (fz_edgebuffer *)ras;
	fixed sx = float2fixed(fsx);
	fixed sy = float2fixed(fsy);
	fixed ex = float2fixed(fex);
	fixed ey = float2fixed(fey);

	mark_line(ctx, eb, sx, sy, ex, ey);
}