#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; } ;
struct sway_workspace {int /*<<< orphan*/  gaps_inner; TYPE_1__ gaps_outer; } ;

/* Variables and functions */

__attribute__((used)) static void prevent_invalid_outer_gaps(struct sway_workspace *ws) {
	if (ws->gaps_outer.top < -ws->gaps_inner) {
		ws->gaps_outer.top = -ws->gaps_inner;
	}
	if (ws->gaps_outer.right < -ws->gaps_inner) {
		ws->gaps_outer.right = -ws->gaps_inner;
	}
	if (ws->gaps_outer.bottom < -ws->gaps_inner) {
		ws->gaps_outer.bottom = -ws->gaps_inner;
	}
	if (ws->gaps_outer.left < -ws->gaps_inner) {
		ws->gaps_outer.left = -ws->gaps_inner;
	}
}