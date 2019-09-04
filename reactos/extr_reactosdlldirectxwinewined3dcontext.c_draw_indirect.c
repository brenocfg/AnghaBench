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
struct wined3d_state {int /*<<< orphan*/  gl_primitive_type; scalar_t__ index_offset; } ;
struct wined3d_indirect_draw_parameters {scalar_t__ offset; struct wined3d_buffer* buffer; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_buffer {int /*<<< orphan*/  buffer_object; } ;
typedef  scalar_t__ GLintptr ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 size_t ARB_DRAW_INDIRECT ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_DRAW_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArraysIndirect (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  glDrawElementsIndirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static void draw_indirect(struct wined3d_context *context, const struct wined3d_state *state,
        const struct wined3d_indirect_draw_parameters *parameters, unsigned int idx_size)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_buffer *buffer = parameters->buffer;
    const void *offset;

    if (!gl_info->supported[ARB_DRAW_INDIRECT])
    {
        FIXME("OpenGL implementation does not support indirect draws.\n");
        return;
    }

    GL_EXTCALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer->buffer_object));

    offset = (void *)(GLintptr)parameters->offset;
    if (idx_size)
    {
        GLenum idx_type = idx_size == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
        if (state->index_offset)
            FIXME("Ignoring index offset %u.\n", state->index_offset);
        GL_EXTCALL(glDrawElementsIndirect(state->gl_primitive_type, idx_type, offset));
    }
    else
    {
        GL_EXTCALL(glDrawArraysIndirect(state->gl_primitive_type, offset));
    }

    GL_EXTCALL(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0));

    checkGLcall("draw indirect");
}