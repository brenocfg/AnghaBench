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
struct wl_listener {int dummy; } ;
struct sway_seat {int dummy; } ;
struct sway_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_node ; 
 struct sway_seat* seat ; 
 int /*<<< orphan*/  seat_node_from_node (struct sway_seat*,struct sway_node*) ; 
 struct sway_seat* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_new_node(struct wl_listener *listener, void *data) {
	struct sway_seat *seat = wl_container_of(listener, seat, new_node);
	struct sway_node *node = data;
	seat_node_from_node(seat, node);
}