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
struct workspace_config {int /*<<< orphan*/  gaps_inner; TYPE_1__ gaps_outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 

__attribute__((used)) static void prevent_invalid_outer_gaps(struct workspace_config *wsc) {
	if (wsc->gaps_outer.top != INT_MIN &&
			wsc->gaps_outer.top < -wsc->gaps_inner) {
		wsc->gaps_outer.top = -wsc->gaps_inner;
	}
	if (wsc->gaps_outer.right != INT_MIN &&
			wsc->gaps_outer.right < -wsc->gaps_inner) {
		wsc->gaps_outer.right = -wsc->gaps_inner;
	}
	if (wsc->gaps_outer.bottom != INT_MIN &&
			wsc->gaps_outer.bottom < -wsc->gaps_inner) {
		wsc->gaps_outer.bottom = -wsc->gaps_inner;
	}
	if (wsc->gaps_outer.left != INT_MIN &&
			wsc->gaps_outer.left < -wsc->gaps_inner) {
		wsc->gaps_outer.left = -wsc->gaps_inner;
	}
}