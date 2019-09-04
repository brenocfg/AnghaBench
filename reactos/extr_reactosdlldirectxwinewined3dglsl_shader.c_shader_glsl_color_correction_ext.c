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
struct color_fixup_desc {int /*<<< orphan*/  w_source; int /*<<< orphan*/  w_sign_fixup; int /*<<< orphan*/  z_source; int /*<<< orphan*/  z_sign_fixup; int /*<<< orphan*/  y_source; int /*<<< orphan*/  y_sign_fixup; int /*<<< orphan*/  x_source; int /*<<< orphan*/  x_sign_fixup; } ;
typedef  enum complex_fixup { ____Placeholder_complex_fixup } complex_fixup ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_SOURCE_W ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_X ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_Y ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_Z ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int WINED3DSP_WRITEMASK_3 ; 
 int get_complex_fixup (struct color_fixup_desc) ; 
 scalar_t__ is_complex_fixup (struct color_fixup_desc) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_append_fixup_arg (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int shader_glsl_get_write_mask_size (int) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void shader_glsl_color_correction_ext(struct wined3d_string_buffer *buffer,
        const char *reg_name, DWORD mask, struct color_fixup_desc fixup)
{
    unsigned int mask_size, remaining;
    DWORD fixup_mask = 0;
    char arguments[256];
    char mask_str[6];

    if (fixup.x_sign_fixup || fixup.x_source != CHANNEL_SOURCE_X) fixup_mask |= WINED3DSP_WRITEMASK_0;
    if (fixup.y_sign_fixup || fixup.y_source != CHANNEL_SOURCE_Y) fixup_mask |= WINED3DSP_WRITEMASK_1;
    if (fixup.z_sign_fixup || fixup.z_source != CHANNEL_SOURCE_Z) fixup_mask |= WINED3DSP_WRITEMASK_2;
    if (fixup.w_sign_fixup || fixup.w_source != CHANNEL_SOURCE_W) fixup_mask |= WINED3DSP_WRITEMASK_3;
    if (!(mask &= fixup_mask))
        return;

    if (is_complex_fixup(fixup))
    {
        enum complex_fixup complex_fixup = get_complex_fixup(fixup);
        FIXME("Complex fixup (%#x) not supported\n",complex_fixup);
        return;
    }

    shader_glsl_write_mask_to_str(mask, mask_str);
    mask_size = shader_glsl_get_write_mask_size(mask);

    arguments[0] = '\0';
    remaining = mask_size;
    if (mask & WINED3DSP_WRITEMASK_0)
    {
        shader_glsl_append_fixup_arg(arguments, reg_name, fixup.x_sign_fixup, fixup.x_source);
        if (--remaining) strcat(arguments, ", ");
    }
    if (mask & WINED3DSP_WRITEMASK_1)
    {
        shader_glsl_append_fixup_arg(arguments, reg_name, fixup.y_sign_fixup, fixup.y_source);
        if (--remaining) strcat(arguments, ", ");
    }
    if (mask & WINED3DSP_WRITEMASK_2)
    {
        shader_glsl_append_fixup_arg(arguments, reg_name, fixup.z_sign_fixup, fixup.z_source);
        if (--remaining) strcat(arguments, ", ");
    }
    if (mask & WINED3DSP_WRITEMASK_3)
    {
        shader_glsl_append_fixup_arg(arguments, reg_name, fixup.w_sign_fixup, fixup.w_source);
        if (--remaining) strcat(arguments, ", ");
    }

    if (mask_size > 1)
        shader_addline(buffer, "%s%s = vec%u(%s);\n", reg_name, mask_str, mask_size, arguments);
    else
        shader_addline(buffer, "%s%s = %s;\n", reg_name, mask_str, arguments);
}