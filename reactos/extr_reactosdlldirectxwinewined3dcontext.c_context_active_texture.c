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
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {unsigned int active_texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glActiveTexture (scalar_t__) ; 

void context_active_texture(struct wined3d_context *context, const struct wined3d_gl_info *gl_info, unsigned int unit)
{
    GL_EXTCALL(glActiveTexture(GL_TEXTURE0 + unit));
    checkGLcall("glActiveTexture");
    context->active_texture = unit;
}