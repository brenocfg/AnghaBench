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
typedef  int /*<<< orphan*/  fz_pool ;
typedef  int /*<<< orphan*/  fz_image ;
struct TYPE_4__ {int /*<<< orphan*/  image; } ;
struct TYPE_5__ {TYPE_1__ content; } ;
typedef  TYPE_2__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_IMAGE ; 
 TYPE_2__* add_flow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_flow_image(fz_context *ctx, fz_pool *pool, fz_html_box *top, fz_html_box *inline_box, fz_image *img)
{
	fz_html_flow *flow = add_flow(ctx, pool, top, inline_box, FLOW_IMAGE, 0);
	flow->content.image = fz_keep_image(ctx, img);
}