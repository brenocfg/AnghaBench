#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_context {int /*<<< orphan*/  aux_buffers; } ;
struct TYPE_2__ {int offscreen_rendering_mode; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GL_AUX0 ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
#define  ORM_BACKBUFFER 129 
#define  ORM_FBO 128 
 TYPE_1__ wined3d_settings ; 

GLenum context_get_offscreen_gl_buffer(const struct wined3d_context *context)
{
    switch (wined3d_settings.offscreen_rendering_mode)
    {
        case ORM_FBO:
            return GL_COLOR_ATTACHMENT0;

        case ORM_BACKBUFFER:
            return context->aux_buffers > 0 ? GL_AUX0 : GL_BACK;

        default:
            FIXME("Unhandled offscreen rendering mode %#x.\n", wined3d_settings.offscreen_rendering_mode);
            return GL_BACK;
    }
}