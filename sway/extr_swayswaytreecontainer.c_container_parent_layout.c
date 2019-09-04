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
struct sway_container {TYPE_2__* workspace; TYPE_1__* parent; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_4__ {int layout; } ;
struct TYPE_3__ {int layout; } ;

/* Variables and functions */
 int L_NONE ; 

enum sway_container_layout container_parent_layout(struct sway_container *con) {
	if (con->parent) {
		return con->parent->layout;
	}
	if (con->workspace) {
		return con->workspace->layout;
	}
	return L_NONE;
}