#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ draw_binding; TYPE_2__* format; struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_5__ resource; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* p_glPixelStorei ) (int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* p_glReadPixels ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glReadBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_3__ gl; } ;
struct wined3d_gl_info {TYPE_4__ gl_ops; } ;
struct wined3d_device {int dummy; } ;
struct TYPE_7__ {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; TYPE_1__ current_rt; } ;
struct wined3d_bo_address {scalar_t__ buffer_object; int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {unsigned int byte_count; int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_PACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_READ_WRITE ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_blit_state (struct wined3d_context*,struct wined3d_device*) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_5__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_get_offscreen_gl_buffer (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glMapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ wined3d_resource_is_offscreen (TYPE_5__*) ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_texture_get_pitch (struct wined3d_texture*,unsigned int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void texture2d_read_from_framebuffer(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        struct wined3d_context *context, DWORD src_location, DWORD dst_location)
{
    struct wined3d_device *device = texture->resource.device;
    struct wined3d_texture *restore_texture;
    const struct wined3d_gl_info *gl_info;
    unsigned int row_pitch, slice_pitch;
    unsigned int width, height, level;
    struct wined3d_bo_address data;
    unsigned int restore_idx;
    BYTE *row, *top, *bottom;
    BOOL src_is_upside_down;
    unsigned int i;
    BYTE *mem;

    wined3d_texture_get_memory(texture, sub_resource_idx, &data, dst_location);

    restore_texture = context->current_rt.texture;
    restore_idx = context->current_rt.sub_resource_idx;
    if (restore_texture != texture || restore_idx != sub_resource_idx)
        context = context_acquire(device, texture, sub_resource_idx);
    else
        restore_texture = NULL;
    gl_info = context->gl_info;

    if (src_location != texture->resource.draw_binding)
    {
        context_apply_fbo_state_blit(context, GL_READ_FRAMEBUFFER,
                &texture->resource, sub_resource_idx, NULL, 0, src_location);
        context_check_fbo_status(context, GL_READ_FRAMEBUFFER);
        context_invalidate_state(context, STATE_FRAMEBUFFER);
    }
    else
    {
        context_apply_blit_state(context, device);
    }

    /* Select the correct read buffer, and give some debug output.
     * There is no need to keep track of the current read buffer or reset it,
     * every part of the code that reads sets the read buffer as desired.
     */
    if (src_location != WINED3D_LOCATION_DRAWABLE || wined3d_resource_is_offscreen(&texture->resource))
    {
        /* Mapping the primary render target which is not on a swapchain.
         * Read from the back buffer. */
        TRACE("Mapping offscreen render target.\n");
        gl_info->gl_ops.gl.p_glReadBuffer(context_get_offscreen_gl_buffer(context));
        src_is_upside_down = TRUE;
    }
    else
    {
        /* Onscreen surfaces are always part of a swapchain */
        GLenum buffer = wined3d_texture_get_gl_buffer(texture);
        TRACE("Mapping %#x buffer.\n", buffer);
        gl_info->gl_ops.gl.p_glReadBuffer(buffer);
        src_is_upside_down = FALSE;
    }
    checkGLcall("glReadBuffer");

    if (data.buffer_object)
    {
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, data.buffer_object));
        checkGLcall("glBindBuffer");
    }

    level = sub_resource_idx % texture->level_count;
    wined3d_texture_get_pitch(texture, level, &row_pitch, &slice_pitch);

    /* Setup pixel store pack state -- to glReadPixels into the correct place */
    gl_info->gl_ops.gl.p_glPixelStorei(GL_PACK_ROW_LENGTH, row_pitch / texture->resource.format->byte_count);
    checkGLcall("glPixelStorei");

    width = wined3d_texture_get_level_width(texture, level);
    height = wined3d_texture_get_level_height(texture, level);
    gl_info->gl_ops.gl.p_glReadPixels(0, 0, width, height,
            texture->resource.format->glFormat,
            texture->resource.format->glType, data.addr);
    checkGLcall("glReadPixels");

    /* Reset previous pixel store pack state */
    gl_info->gl_ops.gl.p_glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    checkGLcall("glPixelStorei");

    if (!src_is_upside_down)
    {
        /* glReadPixels returns the image upside down, and there is no way to
         * prevent this. Flip the lines in software. */

        if (!(row = heap_alloc(row_pitch)))
            goto error;

        if (data.buffer_object)
        {
            mem = GL_EXTCALL(glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_WRITE));
            checkGLcall("glMapBuffer");
        }
        else
            mem = data.addr;

        top = mem;
        bottom = mem + row_pitch * (height - 1);
        for (i = 0; i < height / 2; i++)
        {
            memcpy(row, top, row_pitch);
            memcpy(top, bottom, row_pitch);
            memcpy(bottom, row, row_pitch);
            top += row_pitch;
            bottom -= row_pitch;
        }
        heap_free(row);

        if (data.buffer_object)
            GL_EXTCALL(glUnmapBuffer(GL_PIXEL_PACK_BUFFER));
    }

error:
    if (data.buffer_object)
    {
        GL_EXTCALL(glBindBuffer(GL_PIXEL_PACK_BUFFER, 0));
        checkGLcall("glBindBuffer");
    }

    if (restore_texture)
        context_restore(context, restore_texture, restore_idx);
}