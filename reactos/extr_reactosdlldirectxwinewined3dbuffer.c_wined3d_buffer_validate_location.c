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
struct wined3d_buffer {int locations; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct wined3d_buffer*,...) ; 
 int WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  buffer_clear_dirty_areas (struct wined3d_buffer*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 

__attribute__((used)) static void wined3d_buffer_validate_location(struct wined3d_buffer *buffer, DWORD location)
{
    TRACE("buffer %p, location %s.\n", buffer, wined3d_debug_location(location));

    if (location & WINED3D_LOCATION_BUFFER)
        buffer_clear_dirty_areas(buffer);

    buffer->locations |= location;

    TRACE("New locations flags are %s.\n", wined3d_debug_location(buffer->locations));
}