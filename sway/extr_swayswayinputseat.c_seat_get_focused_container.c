#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_seat {int dummy; } ;
struct sway_node {scalar_t__ type; struct sway_container* sway_container; } ;
struct sway_container {int dummy; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 

struct sway_container *seat_get_focused_container(struct sway_seat *seat) {
	struct sway_node *focus = seat_get_focus(seat);
	if (focus && focus->type == N_CONTAINER) {
		return focus->sway_container;
	}
	return NULL;
}