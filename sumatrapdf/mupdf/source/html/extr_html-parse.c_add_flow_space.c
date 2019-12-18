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
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_3__ {int expand; } ;
typedef  TYPE_1__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_SPACE ; 
 TYPE_1__* add_flow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_flow_space(fz_context *ctx, fz_pool *pool, fz_html_box *top, fz_html_box *inline_box)
{
	fz_html_flow *flow = add_flow(ctx, pool, top, inline_box, FLOW_SPACE, 0);
	flow->expand = 1;
}