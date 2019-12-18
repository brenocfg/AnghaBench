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
struct sway_seat_node {struct sway_node* node; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct sway_seat {TYPE_1__ focus_stack; int /*<<< orphan*/  has_focus; } ;
struct sway_node {int dummy; } ;

/* Variables and functions */
 struct sway_seat_node* current ; 
 int /*<<< orphan*/  link ; 
 struct sway_seat_node* wl_container_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wl_list_empty (TYPE_1__*) ; 

struct sway_node *seat_get_focus(struct sway_seat *seat) {
	if (!seat->has_focus) {
		return NULL;
	}
	if (wl_list_empty(&seat->focus_stack)) {
		return NULL;
	}
	struct sway_seat_node *current =
		wl_container_of(seat->focus_stack.next, current, link);
	return current->node;
}