#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wmode; TYPE_1__* items; int /*<<< orphan*/  font; } ;
typedef  TYPE_2__ fz_text_span ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int gid; } ;

/* Variables and functions */
 int fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float
svg_cluster_advance(fz_context *ctx, const fz_text_span *span, int i, int end)
{
	int n = 1;
	while (i + n < end && span->items[i + n].gid == -1)
		++n;
	if (n > 1)
		return fz_advance_glyph(ctx, span->font, span->items[i].gid, span->wmode) / n;
	return 0; /* this value is never used (since n==1) */
}