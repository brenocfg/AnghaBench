#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* fontdesc; } ;
struct TYPE_13__ {float Tm_adjust; TYPE_5__* gstate; TYPE_2__ tos; } ;
typedef  TYPE_6__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {float size; } ;
struct TYPE_11__ {TYPE_3__ text; } ;
struct TYPE_12__ {TYPE_4__ pending; } ;
struct TYPE_8__ {int wmode; } ;

/* Variables and functions */

__attribute__((used)) static void
adjust_text(fz_context *ctx, pdf_filter_processor *p, float x, float y)
{
	float skip_dist = p->tos.fontdesc->wmode == 1 ? -y : -x;
	skip_dist = skip_dist / p->gstate->pending.text.size;
	p->Tm_adjust += skip_dist;
}