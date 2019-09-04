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

__attribute__((used)) static BOOL shader_glsl_use_interface_blocks(const struct wined3d_gl_info *gl_info)
{
    return shader_glsl_get_version(gl_info) >= 150;
}