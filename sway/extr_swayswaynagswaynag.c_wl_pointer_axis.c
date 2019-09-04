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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_pointer {int dummy; } ;
struct TYPE_4__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; scalar_t__ total_lines; scalar_t__ visible_lines; int offset; int /*<<< orphan*/  visible; } ;
struct TYPE_3__ {scalar_t__ x; scalar_t__ y; } ;
struct swaynag {TYPE_2__ details; TYPE_1__ pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  render_frame (struct swaynag*) ; 
 int wl_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl_pointer_axis(void *data, struct wl_pointer *wl_pointer,
		uint32_t time, uint32_t axis, wl_fixed_t value) {
	struct swaynag *swaynag = data;
	if (!swaynag->details.visible
			|| swaynag->pointer.x < swaynag->details.x
			|| swaynag->pointer.y < swaynag->details.y
			|| swaynag->pointer.x >= swaynag->details.x + swaynag->details.width
			|| swaynag->pointer.y >= swaynag->details.y + swaynag->details.height
			|| swaynag->details.total_lines == swaynag->details.visible_lines) {
		return;
	}

	int direction = wl_fixed_to_int(value);
	int bot = swaynag->details.total_lines - swaynag->details.visible_lines;
	if (direction < 0 && swaynag->details.offset > 0) {
		swaynag->details.offset--;
	} else if (direction > 0 && swaynag->details.offset < bot) {
		swaynag->details.offset++;
	}

	render_frame(swaynag);
}