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
typedef  int BOOL ;

/* Variables and functions */
 int shader_glsl_get_version (struct wined3d_gl_info const*) ; 

__attribute__((used)) static BOOL shader_glsl_use_layout_qualifier(const struct wined3d_gl_info *gl_info)
{
    /* Layout qualifiers were introduced in GLSL 1.40. The Nvidia Legacy GPU
     * driver (series 340.xx) doesn't parse layout qualifiers in older GLSL
     * versions. */
    return shader_glsl_get_version(gl_info) >= 140;
}