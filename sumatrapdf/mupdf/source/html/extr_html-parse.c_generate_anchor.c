#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct genstate {int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* up; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ BOX_FLOW ; 
 int /*<<< orphan*/  add_flow_anchor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void generate_anchor(fz_context *ctx, fz_html_box *box, struct genstate *g)
{
	fz_pool *pool = g->pool;
	fz_html_box *flow = box;
	while (flow->type != BOX_FLOW)
		flow = flow->up;
	add_flow_anchor(ctx, pool, flow, box);
}