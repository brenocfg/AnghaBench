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
struct wined3d_context {unsigned int numbered_array_mask; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 size_t ARB_INSTANCED_ARRAYS ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (unsigned int) ; 
 int /*<<< orphan*/  glVertexAttribDivisor (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_unload_numbered_array(struct wined3d_context *context, unsigned int i)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    GL_EXTCALL(glDisableVertexAttribArray(i));
    checkGLcall("glDisableVertexAttribArray");
    if (gl_info->supported[ARB_INSTANCED_ARRAYS])
        GL_EXTCALL(glVertexAttribDivisor(i, 0));

    context->numbered_array_mask &= ~(1u << i);
}