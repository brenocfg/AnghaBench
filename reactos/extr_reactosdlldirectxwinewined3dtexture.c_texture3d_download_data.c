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
struct TYPE_6__ {struct wined3d_format* format; } ;
struct wined3d_texture {TYPE_3__ resource; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_glGetTexImage ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_format {int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; int /*<<< orphan*/  id; scalar_t__ conv_byte_count; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_bo_address {scalar_t__ buffer_object; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void texture3d_download_data(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        const struct wined3d_context *context, const struct wined3d_bo_address *data)
{
    const struct wined3d_format *format = texture->resource.format;
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (format->conv_byte_count)
    {
        FIXME("Attempting to download a converted volume, format %s.\n",
                debug_d3dformat(format->id));
        return;
    }

    if (data->buffer_object)
    {
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, data->buffer_object));
        checkGLcall("glBindBuffer");
    }

    gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_3D, sub_resource_idx,
            format->glFormat, format->glType, data->addr);
    checkGLcall("glGetTexImage");

    if (data->buffer_object)
    {
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, 0));
        checkGLcall("glBindBuffer");
    }

}