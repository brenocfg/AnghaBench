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
typedef  int /*<<< orphan*/  fz_edgebuffer ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fixed ;

/* Variables and functions */
 int /*<<< orphan*/  do_mark_line_app (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mark_line_app(fz_context *ctx, fz_edgebuffer *eb, fixed sx, fixed sy, fixed ex, fixed ey, int rev)
{
	if (rev == 1)
	{
		fixed t;
		t = sx, sx = ex, ex = t;
		t = sy, sy = ey, ey = t;
	}
	do_mark_line_app(ctx, eb, sx, sy, ex, ey, rev);
}