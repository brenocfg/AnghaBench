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
struct wined3d_shader_dst_param {int /*<<< orphan*/  reg; int /*<<< orphan*/  write_mask; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ shader_is_scalar (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD shader_glsl_get_write_mask(const struct wined3d_shader_dst_param *param, char *write_mask)
{
    DWORD mask = param->write_mask;

    if (shader_is_scalar(&param->reg))
    {
        mask = WINED3DSP_WRITEMASK_0;
        *write_mask = '\0';
    }
    else
    {
        shader_glsl_write_mask_to_str(mask, write_mask);
    }

    return mask;
}