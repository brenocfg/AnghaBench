#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* p_glDisableClientState ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_glClientActiveTextureARB ) (scalar_t__) ;} ;
struct TYPE_8__ {TYPE_3__ gl; TYPE_2__ ext; } ;
struct TYPE_5__ {unsigned int texture_coords; } ;
struct wined3d_gl_info {TYPE_4__ gl_ops; TYPE_1__ limits; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE0_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void context_unload_tex_coords(const struct wined3d_context *context)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int texture_idx;

    for (texture_idx = 0; texture_idx < gl_info->limits.texture_coords; ++texture_idx)
    {
        gl_info->gl_ops.ext.p_glClientActiveTextureARB(GL_TEXTURE0_ARB + texture_idx);
        gl_info->gl_ops.gl.p_glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}