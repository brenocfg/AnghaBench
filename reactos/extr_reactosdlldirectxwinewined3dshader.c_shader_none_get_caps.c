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
struct shader_caps {float ps_1x_max_value; scalar_t__ wined3d_caps; scalar_t__ varying_count; scalar_t__ ps_uniform_count; scalar_t__ vs_uniform_count; scalar_t__ cs_version; scalar_t__ ps_version; scalar_t__ gs_version; scalar_t__ ds_version; scalar_t__ hs_version; scalar_t__ vs_version; } ;

/* Variables and functions */

__attribute__((used)) static void shader_none_get_caps(const struct wined3d_gl_info *gl_info, struct shader_caps *caps)
{
    /* Set the shader caps to 0 for the none shader backend */
    caps->vs_version = 0;
    caps->hs_version = 0;
    caps->ds_version = 0;
    caps->gs_version = 0;
    caps->ps_version = 0;
    caps->cs_version = 0;
    caps->vs_uniform_count = 0;
    caps->ps_uniform_count = 0;
    caps->ps_1x_max_value = 0.0f;
    caps->varying_count = 0;
    caps->wined3d_caps = 0;
}