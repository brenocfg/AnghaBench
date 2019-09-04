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
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;

/* Variables and functions */
#define  WLR_DIRECTION_DOWN 131 
#define  WLR_DIRECTION_LEFT 130 
#define  WLR_DIRECTION_RIGHT 129 
#define  WLR_DIRECTION_UP 128 
 int /*<<< orphan*/  assert (int) ; 

enum wlr_direction opposite_direction(enum wlr_direction d) {
	switch (d) {
	case WLR_DIRECTION_UP:
		return WLR_DIRECTION_DOWN;
	case WLR_DIRECTION_DOWN:
		return WLR_DIRECTION_UP;
	case WLR_DIRECTION_RIGHT:
		return WLR_DIRECTION_LEFT;
	case WLR_DIRECTION_LEFT:
		return WLR_DIRECTION_RIGHT;
	}
	assert(false);
	return 0;
}