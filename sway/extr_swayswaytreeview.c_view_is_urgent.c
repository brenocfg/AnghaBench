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
struct TYPE_2__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct sway_view {TYPE_1__ urgent; } ;

/* Variables and functions */

bool view_is_urgent(struct sway_view *view) {
	return view->urgent.tv_sec || view->urgent.tv_nsec;
}