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
struct wined3d_device {size_t context_count; struct wined3d_context** contexts; } ;
struct wined3d_context {int dummy; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  heap_free (struct wined3d_context**) ; 
 struct wined3d_context** heap_realloc (struct wined3d_context**,int) ; 
 int /*<<< orphan*/  memmove (struct wined3d_context**,struct wined3d_context**,size_t) ; 

void device_context_remove(struct wined3d_device *device, struct wined3d_context *context)
{
    struct wined3d_context **new_array;
    BOOL found = FALSE;
    UINT i;

    TRACE("Removing context %p.\n", context);

    for (i = 0; i < device->context_count; ++i)
    {
        if (device->contexts[i] == context)
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        ERR("Context %p doesn't exist in context array.\n", context);
        return;
    }

    if (!--device->context_count)
    {
        heap_free(device->contexts);
        device->contexts = NULL;
        return;
    }

    memmove(&device->contexts[i], &device->contexts[i + 1], (device->context_count - i) * sizeof(*device->contexts));
    if (!(new_array = heap_realloc(device->contexts, device->context_count * sizeof(*device->contexts))))
    {
        ERR("Failed to shrink context array. Oh well.\n");
        return;
    }

    device->contexts = new_array;
}