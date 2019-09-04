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
 unsigned int get_attribute_keyword (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,unsigned int,char const*,char const*,unsigned int) ; 

__attribute__((used)) static void shader_glsl_declare_typed_vertex_attribute(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const char *vector_type, const char *scalar_type,
        unsigned int index)
{
    shader_addline(buffer, "%s %s4 vs_in_%s%u;\n",
            get_attribute_keyword(gl_info), vector_type, scalar_type, index);
    shader_addline(buffer, "vec4 vs_in%u = %sBitsToFloat(vs_in_%s%u);\n",
            index, scalar_type, scalar_type, index);
}