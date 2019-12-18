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
struct highlight {int len; int cap; float hfuzz; float vfuzz; int /*<<< orphan*/ * box; } ;
struct callbacks {struct highlight* arg; int /*<<< orphan*/  on_line; int /*<<< orphan*/  on_char; } ;
typedef  int /*<<< orphan*/  fz_stext_page ;
typedef  int /*<<< orphan*/  fz_quad ;
typedef  int /*<<< orphan*/  fz_point ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_enumerate_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callbacks*) ; 
 int /*<<< orphan*/  on_highlight_char ; 
 int /*<<< orphan*/  on_highlight_line ; 

int
fz_highlight_selection(fz_context *ctx, fz_stext_page *page, fz_point a, fz_point b, fz_quad *quads, int max_quads)
{
	struct callbacks cb;
	struct highlight hits;

	hits.len = 0;
	hits.cap = max_quads;
	hits.box = quads;
	hits.hfuzz = 0.5f; /* merge large gaps */
	hits.vfuzz = 0.1f;

	cb.on_char = on_highlight_char;
	cb.on_line = on_highlight_line;
	cb.arg = &hits;

	fz_enumerate_selection(ctx, page, a, b, &cb);

	return hits.len;
}