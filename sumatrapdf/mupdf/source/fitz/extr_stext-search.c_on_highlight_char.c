#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct highlight {float vfuzz; float hfuzz; int len; int cap; TYPE_3__* box; } ;
struct TYPE_6__ {int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ fz_stext_line ;
struct TYPE_8__ {int /*<<< orphan*/  lr; int /*<<< orphan*/  ur; int /*<<< orphan*/  ul; int /*<<< orphan*/  ll; } ;
struct TYPE_7__ {float size; TYPE_3__ quad; } ;
typedef  TYPE_2__ fz_stext_char ;
typedef  TYPE_3__ fz_quad ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float hdist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float vdist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_highlight_char(fz_context *ctx, void *arg, fz_stext_line *line, fz_stext_char *ch)
{
	struct highlight *hits = arg;
	float vfuzz = ch->size * hits->vfuzz;
	float hfuzz = ch->size * hits->hfuzz;

	if (hits->len > 0)
	{
		fz_quad *end = &hits->box[hits->len-1];
		if (hdist(&line->dir, &end->lr, &ch->quad.ll) < hfuzz
			&& vdist(&line->dir, &end->lr, &ch->quad.ll) < vfuzz
			&& hdist(&line->dir, &end->ur, &ch->quad.ul) < hfuzz
			&& vdist(&line->dir, &end->ur, &ch->quad.ul) < vfuzz)
		{
			end->ur = ch->quad.ur;
			end->lr = ch->quad.lr;
			return;
		}
	}

	if (hits->len < hits->cap)
		hits->box[hits->len++] = ch->quad;
}