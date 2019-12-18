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
struct sway_container {scalar_t__ fullscreen_mode; TYPE_1__* workspace; } ;
struct TYPE_2__ {struct sway_container* fullscreen; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_WORKSPACE ; 
 int /*<<< orphan*/  arrange_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  container_fullscreen_disable (struct sway_container*) ; 

void container_handle_fullscreen_reparent(struct sway_container *con) {
	if (con->fullscreen_mode != FULLSCREEN_WORKSPACE || !con->workspace ||
			con->workspace->fullscreen == con) {
		return;
	}
	if (con->workspace->fullscreen) {
		container_fullscreen_disable(con->workspace->fullscreen);
	}
	con->workspace->fullscreen = con;

	arrange_workspace(con->workspace);
}