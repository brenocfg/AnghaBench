#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_4__ {scalar_t__ server_depth; scalar_t__ width; scalar_t__ height; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_resize_window (TYPE_1__*) ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static void
rdp_process_bitmap_caps(RDPCLIENT * This, STREAM s)
{
	uint16 width, height, depth;

	in_uint16_le(s, depth);
	in_uint8s(s, 6);

	in_uint16_le(s, width);
	in_uint16_le(s, height);

	DEBUG(("setting desktop size and depth to: %dx%dx%d\n", width, height, depth));

	/*
	 * The server may limit depth and change the size of the desktop (for
	 * example when shadowing another session).
	 */
	if (This->server_depth != depth)
	{
		warning("Remote desktop does not support colour depth %d; falling back to %d\n",
			This->server_depth, depth);
		This->server_depth = depth;
	}
	if (This->width != width || This->height != height)
	{
		warning("Remote desktop changed from %dx%d to %dx%d.\n", This->width, This->height,
			width, height);
		This->width = width;
		This->height = height;
		ui_resize_window(This);
	}
}