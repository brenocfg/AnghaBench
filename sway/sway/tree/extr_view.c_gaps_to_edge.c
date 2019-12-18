#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_view {TYPE_2__* container; } ;
struct side_gaps {scalar_t__ top; scalar_t__ right; scalar_t__ bottom; scalar_t__ left; } ;
struct TYPE_4__ {TYPE_1__* workspace; } ;
struct TYPE_3__ {struct side_gaps current_gaps; } ;

/* Variables and functions */

__attribute__((used)) static bool gaps_to_edge(struct sway_view *view) {
	struct side_gaps gaps = view->container->workspace->current_gaps;
	return gaps.top > 0 || gaps.right > 0 || gaps.bottom > 0 || gaps.left > 0;
}