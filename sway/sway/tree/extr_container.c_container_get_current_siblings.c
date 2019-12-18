#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* workspace; TYPE_2__* parent; } ;
struct sway_container {TYPE_5__ current; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_8__ {int /*<<< orphan*/ * tiling; } ;
struct TYPE_9__ {TYPE_3__ current; } ;
struct TYPE_6__ {int /*<<< orphan*/ * children; } ;
struct TYPE_7__ {TYPE_1__ current; } ;

/* Variables and functions */

list_t *container_get_current_siblings(struct sway_container *container) {
	if (container->current.parent) {
		return container->current.parent->current.children;
	}
	return container->current.workspace->current.tiling;
}