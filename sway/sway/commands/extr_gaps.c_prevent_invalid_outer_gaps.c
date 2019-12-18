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
struct TYPE_3__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; } ;
struct TYPE_4__ {int /*<<< orphan*/  gaps_inner; TYPE_1__ gaps_outer; } ;

/* Variables and functions */
 TYPE_2__* config ; 

__attribute__((used)) static void prevent_invalid_outer_gaps(void) {
	if (config->gaps_outer.top < -config->gaps_inner) {
		config->gaps_outer.top = -config->gaps_inner;
	}
	if (config->gaps_outer.right < -config->gaps_inner) {
		config->gaps_outer.right = -config->gaps_inner;
	}
	if (config->gaps_outer.bottom < -config->gaps_inner) {
		config->gaps_outer.bottom = -config->gaps_inner;
	}
	if (config->gaps_outer.left < -config->gaps_inner) {
		config->gaps_outer.left = -config->gaps_inner;
	}
}