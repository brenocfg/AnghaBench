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
struct wined3d_texture {int flags; } ;
struct wined3d_resource {int /*<<< orphan*/  device; } ;
struct wined3d_context {int dummy; } ;

/* Variables and functions */
 int WINED3D_TEXTURE_IS_SRGB ; 
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 struct wined3d_texture* texture_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_texture_load (struct wined3d_texture*,struct wined3d_context*,int) ; 

__attribute__((used)) static void texture_resource_preload(struct wined3d_resource *resource)
{
    struct wined3d_texture *texture = texture_from_resource(resource);
    struct wined3d_context *context;

    context = context_acquire(resource->device, NULL, 0);
    wined3d_texture_load(texture, context, texture->flags & WINED3D_TEXTURE_IS_SRGB);
    context_release(context);
}