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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct swaynag_pointer {int /*<<< orphan*/  serial; } ;
struct swaynag {struct swaynag_pointer pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_cursor (struct swaynag*) ; 

__attribute__((used)) static void wl_pointer_enter(void *data, struct wl_pointer *wl_pointer,
		uint32_t serial, struct wl_surface *surface,
		wl_fixed_t surface_x, wl_fixed_t surface_y) {
	struct swaynag *swaynag = data;
	struct swaynag_pointer *pointer = &swaynag->pointer;
	pointer->serial = serial;
	update_cursor(swaynag);
}