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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_version (struct wined3d_gl_info const*) ; 

__attribute__((used)) static void shader_glsl_add_version_declaration(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info)
{
    shader_addline(buffer, "#version %u\n", shader_glsl_get_version(gl_info));
}