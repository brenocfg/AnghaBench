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
struct TYPE_4__ {float flatness; float linewidth; } ;
typedef  TYPE_1__ sctx ;
typedef  int fz_linecap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  FZ_LINECAP_BUTT 131 
#define  FZ_LINECAP_ROUND 130 
#define  FZ_LINECAP_SQUARE 129 
#define  FZ_LINECAP_TRIANGLE 128 
 float FZ_PI ; 
 float FZ_SQRT2 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ceilf (float) ; 
 float cosf (float) ; 
 int /*<<< orphan*/  fz_add_line (int /*<<< orphan*/ *,TYPE_1__*,float,float,float,float,int) ; 
 float sinf (float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void
fz_add_line_cap(fz_context *ctx, sctx *s, float ax, float ay, float bx, float by, fz_linecap linecap, int rev)
{
	float flatness = s->flatness;
	float linewidth = s->linewidth;

	float dx = bx - ax;
	float dy = by - ay;

	float scale = linewidth / sqrtf(dx * dx + dy * dy);
	float dlx = dy * scale;
	float dly = -dx * scale;

	switch (linecap)
	{
	case FZ_LINECAP_BUTT:
		fz_add_line(ctx, s, bx - dlx, by - dly, bx + dlx, by + dly, rev);
		break;

	case FZ_LINECAP_ROUND:
	{
		int i;
		int n = ceilf(FZ_PI / (2.0f * FZ_SQRT2 * sqrtf(flatness / linewidth)));
		float ox = bx - dlx;
		float oy = by - dly;
		for (i = 1; i < n; i++)
		{
			float theta = FZ_PI * i / n;
			float cth = cosf(theta);
			float sth = sinf(theta);
			float nx = bx - dlx * cth - dly * sth;
			float ny = by - dly * cth + dlx * sth;
			fz_add_line(ctx, s, ox, oy, nx, ny, rev);
			ox = nx;
			oy = ny;
		}
		fz_add_line(ctx, s, ox, oy, bx + dlx, by + dly, rev);
		break;
	}

	case FZ_LINECAP_SQUARE:
		fz_add_line(ctx, s, bx - dlx, by - dly,
			bx - dlx - dly, by - dly + dlx, rev);
		fz_add_line(ctx, s, bx - dlx - dly, by - dly + dlx,
			bx + dlx - dly, by + dly + dlx, rev);
		fz_add_line(ctx, s, bx + dlx - dly, by + dly + dlx,
			bx + dlx, by + dly, rev);
		break;

	case FZ_LINECAP_TRIANGLE:
	{
		float mx = -dly;
		float my = dlx;
		fz_add_line(ctx, s, bx - dlx, by - dly, bx + mx, by + my, rev);
		fz_add_line(ctx, s, bx + mx, by + my, bx + dlx, by + dly, rev);
		break;
	}

	default:
		assert("Invalid line cap" == NULL);
	}
}