#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {TYPE_3__* adapter; TYPE_1__* shader_backend; int /*<<< orphan*/  cs; } ;
struct wined3d_context {int destroy_delayed; scalar_t__ tid; int destroyed; struct wined3d_context* texture_type; struct wined3d_gl_info* gl_info; int /*<<< orphan*/  current; int /*<<< orphan*/ * swapchain; scalar_t__ level; } ;
struct TYPE_6__ {TYPE_2__* fragment_pipe; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* free_context_data ) (struct wined3d_context*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* shader_free_context_data ) (struct wined3d_context*) ;} ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_destroy_gl_resources (struct wined3d_context*) ; 
 int /*<<< orphan*/  device_context_remove (struct wined3d_device*,struct wined3d_context*) ; 
 struct wined3d_gl_info* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct wined3d_context*) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_context*) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_context*) ; 
 int /*<<< orphan*/  wined3d_context_tls_idx ; 
 int /*<<< orphan*/  wined3d_from_cs (int /*<<< orphan*/ ) ; 

void context_destroy(struct wined3d_device *device, struct wined3d_context *context)
{
    BOOL destroy;

    TRACE("Destroying ctx %p\n", context);

    wined3d_from_cs(device->cs);

    /* We delay destroying a context when it is active. The context_release()
     * function invokes context_destroy() again while leaving the last level. */
    if (context->level)
    {
        TRACE("Delaying destruction of context %p.\n", context);
        context->destroy_delayed = 1;
        /* FIXME: Get rid of a pointer to swapchain from wined3d_context. */
        context->swapchain = NULL;
        return;
    }

    if (context->tid == GetCurrentThreadId() || !context->current)
    {
        context_destroy_gl_resources(context);
        TlsSetValue(wined3d_context_tls_idx, NULL);
        destroy = TRUE;
    }
    else
    {
        /* Make a copy of gl_info for context_destroy_gl_resources use, the one
           in wined3d_adapter may go away in the meantime */
        struct wined3d_gl_info *gl_info = heap_alloc(sizeof(*gl_info));
        *gl_info = *context->gl_info;
        context->gl_info = gl_info;
        context->destroyed = 1;
        destroy = FALSE;
    }

    device->shader_backend->shader_free_context_data(context);
    device->adapter->fragment_pipe->free_context_data(context);
    heap_free(context->texture_type);
    device_context_remove(device, context);
    if (destroy)
        heap_free(context);
}