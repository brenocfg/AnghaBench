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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_bo_address {int /*<<< orphan*/ * addr; scalar_t__ buffer_object; } ;
typedef  int /*<<< orphan*/  GLintptr ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ARB_COPY_BUFFER ; 
 int /*<<< orphan*/  GL_COPY_READ_BUFFER ; 
 int /*<<< orphan*/  GL_COPY_WRITE_BUFFER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_MAP_READ ; 
 int /*<<< orphan*/  WINED3D_MAP_WRITE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_bo (struct wined3d_context*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * context_map_bo_address (struct wined3d_context*,struct wined3d_bo_address const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_unmap_bo_address (struct wined3d_context*,struct wined3d_bo_address const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glCopyBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  glGetBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void context_copy_bo_address(struct wined3d_context *context,
        const struct wined3d_bo_address *dst, GLenum dst_binding,
        const struct wined3d_bo_address *src, GLenum src_binding, size_t size)
{
    const struct wined3d_gl_info *gl_info;
    BYTE *dst_ptr, *src_ptr;

    gl_info = context->gl_info;

    if (dst->buffer_object && src->buffer_object)
    {
        if (gl_info->supported[ARB_COPY_BUFFER])
        {
            GL_EXTCALL(glBindBuffer(GL_COPY_READ_BUFFER, src->buffer_object));
            GL_EXTCALL(glBindBuffer(GL_COPY_WRITE_BUFFER, dst->buffer_object));
            GL_EXTCALL(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,
                    (GLintptr)src->addr, (GLintptr)dst->addr, size));
            checkGLcall("direct buffer copy");
        }
        else
        {
            src_ptr = context_map_bo_address(context, src, size, src_binding, WINED3D_MAP_READ);
            dst_ptr = context_map_bo_address(context, dst, size, dst_binding, WINED3D_MAP_WRITE);

            memcpy(dst_ptr, src_ptr, size);

            context_unmap_bo_address(context, dst, dst_binding);
            context_unmap_bo_address(context, src, src_binding);
        }
    }
    else if (!dst->buffer_object && src->buffer_object)
    {
        context_bind_bo(context, src_binding, src->buffer_object);
        GL_EXTCALL(glGetBufferSubData(src_binding, (GLintptr)src->addr, size, dst->addr));
        checkGLcall("buffer download");
    }
    else if (dst->buffer_object && !src->buffer_object)
    {
        context_bind_bo(context, dst_binding, dst->buffer_object);
        GL_EXTCALL(glBufferSubData(dst_binding, (GLintptr)dst->addr, size, src->addr));
        checkGLcall("buffer upload");
    }
    else
    {
        memcpy(dst->addr, src->addr, size);
    }
}