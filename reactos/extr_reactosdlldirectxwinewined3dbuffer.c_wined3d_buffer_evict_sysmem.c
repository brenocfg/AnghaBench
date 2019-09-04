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
struct wined3d_buffer {int flags; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct wined3d_buffer*) ; 
 int WINED3D_BUFFER_PIN_SYSMEM ; 
 int /*<<< orphan*/  WINED3D_LOCATION_SYSMEM ; 
 int /*<<< orphan*/  wined3d_buffer_invalidate_location (struct wined3d_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_free_sysmem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wined3d_buffer_evict_sysmem(struct wined3d_buffer *buffer)
{
    if (buffer->flags & WINED3D_BUFFER_PIN_SYSMEM)
    {
        TRACE("Not evicting system memory for buffer %p.\n", buffer);
        return;
    }

    TRACE("Evicting system memory for buffer %p.\n", buffer);
    wined3d_buffer_invalidate_location(buffer, WINED3D_LOCATION_SYSMEM);
    wined3d_resource_free_sysmem(&buffer->resource);
}