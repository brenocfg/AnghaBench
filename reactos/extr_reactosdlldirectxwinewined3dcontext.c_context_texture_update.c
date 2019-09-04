#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ name; } ;
struct TYPE_7__ {scalar_t__ name; } ;
struct wined3d_texture {TYPE_3__ texture_srgb; TYPE_2__ texture_rgb; } ;
struct TYPE_6__ {int buffers; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct wined3d_context {scalar_t__ rebind_fbo; struct fbo_entry* current_fbo; struct wined3d_gl_info* gl_info; } ;
struct TYPE_10__ {TYPE_4__* objects; } ;
struct fbo_entry {TYPE_5__ key; } ;
struct TYPE_9__ {scalar_t__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture const*,unsigned int) ; 
 scalar_t__ TRUE ; 

void context_texture_update(struct wined3d_context *context, const struct wined3d_texture *texture)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct fbo_entry *entry = context->current_fbo;
    unsigned int i;

    if (!entry || context->rebind_fbo) return;

    for (i = 0; i < gl_info->limits.buffers + 1; ++i)
    {
        if (texture->texture_rgb.name == entry->key.objects[i].object
                || texture->texture_srgb.name == entry->key.objects[i].object)
        {
            TRACE("Updated texture %p is bound as attachment %u to the current FBO.\n", texture, i);
            context->rebind_fbo = TRUE;
            return;
        }
    }
}