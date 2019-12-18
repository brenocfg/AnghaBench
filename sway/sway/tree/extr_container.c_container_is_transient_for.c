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
struct sway_container {scalar_t__ view; } ;
struct TYPE_2__ {scalar_t__ popup_during_fullscreen; } ;

/* Variables and functions */
 scalar_t__ POPUP_SMART ; 
 TYPE_1__* config ; 
 scalar_t__ view_is_transient_for (scalar_t__,scalar_t__) ; 

bool container_is_transient_for(struct sway_container *child,
		struct sway_container *ancestor) {
	return config->popup_during_fullscreen == POPUP_SMART &&
		child->view && ancestor->view &&
		view_is_transient_for(child->view, ancestor->view);
}