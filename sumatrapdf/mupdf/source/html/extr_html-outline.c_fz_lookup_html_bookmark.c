#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y; } ;
typedef  TYPE_1__ fz_html_flow ;
struct TYPE_6__ {int page_h; int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ fz_html ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ fz_bookmark ;

/* Variables and functions */
 scalar_t__ lookup_box_bookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

int
fz_lookup_html_bookmark(fz_context *ctx, fz_html *html, fz_bookmark mark)
{
	fz_html_flow *flow = (fz_html_flow*)mark;
	if (flow && lookup_box_bookmark(ctx, html->root, flow))
		return (int)(flow->y / html->page_h);
	return -1;
}