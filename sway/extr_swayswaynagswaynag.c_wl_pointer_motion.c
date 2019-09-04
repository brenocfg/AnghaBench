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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_pointer {int dummy; } ;
struct TYPE_2__ {void* y; void* x; } ;
struct swaynag {TYPE_1__ pointer; } ;

/* Variables and functions */
 void* wl_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl_pointer_motion(void *data, struct wl_pointer *wl_pointer,
		uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y) {
	struct swaynag *swaynag = data;
	swaynag->pointer.x = wl_fixed_to_int(surface_x);
	swaynag->pointer.y = wl_fixed_to_int(surface_y);
}