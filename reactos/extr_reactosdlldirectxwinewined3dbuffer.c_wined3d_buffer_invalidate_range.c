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
 int /*<<< orphan*/  ERR (char*,struct wined3d_buffer*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_buffer*,...) ; 
 int WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  buffer_invalidate_bo_range (struct wined3d_buffer*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 

__attribute__((used)) static void wined3d_buffer_invalidate_range(struct wined3d_buffer *buffer, DWORD location,
        unsigned int offset, unsigned int size)
{
    TRACE("buffer %p, location %s, offset %u, size %u.\n",
            buffer, wined3d_debug_location(location), offset, size);

    if (location & WINED3D_LOCATION_BUFFER)
        buffer_invalidate_bo_range(buffer, offset, size);

    buffer->locations &= ~location;

    TRACE("New locations flags are %s.\n", wined3d_debug_location(buffer->locations));

    if (!buffer->locations)
        ERR("Buffer %p does not have any up to date location.\n", buffer);
}