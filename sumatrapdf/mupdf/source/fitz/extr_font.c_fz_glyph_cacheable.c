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
struct TYPE_3__ {int* t3flags; int glyph_count; int /*<<< orphan*/  t3procs; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_DEVFLAG_UNCACHEABLE ; 

int fz_glyph_cacheable(fz_context *ctx, fz_font *font, int gid)
{
	if (!font->t3procs || !font->t3flags || gid < 0 || gid >= font->glyph_count)
		return 1;
	return (font->t3flags[gid] & FZ_DEVFLAG_UNCACHEABLE) == 0;
}