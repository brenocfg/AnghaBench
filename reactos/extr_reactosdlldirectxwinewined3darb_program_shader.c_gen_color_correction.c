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
struct color_fixup_masks {int sign; scalar_t__ source; } ;
struct color_fixup_desc {int /*<<< orphan*/  w_source; int /*<<< orphan*/  z_source; int /*<<< orphan*/  y_source; int /*<<< orphan*/  x_source; } ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int WINED3DSP_WRITEMASK_3 ; 
 int WINED3DSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,char const*,char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/  shader_arb_get_fixup_swizzle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen_color_correction(struct wined3d_string_buffer *buffer, const char *dst,
        const char *src, const char *one, const char *two,
        struct color_fixup_desc fixup, struct color_fixup_masks masks)
{
    const char *sign_fixup_src = dst;

    if (masks.source)
    {
        if (masks.sign)
            sign_fixup_src = "TA";

        shader_addline(buffer, "SWZ %s, %s, %s, %s, %s, %s;\n", sign_fixup_src, src,
                shader_arb_get_fixup_swizzle(fixup.x_source), shader_arb_get_fixup_swizzle(fixup.y_source),
                shader_arb_get_fixup_swizzle(fixup.z_source), shader_arb_get_fixup_swizzle(fixup.w_source));
    }
    else if (masks.sign)
    {
        sign_fixup_src = src;
    }

    if (masks.sign)
    {
        char reg_mask[6];
        char *ptr = reg_mask;

        if (masks.sign != WINED3DSP_WRITEMASK_ALL)
        {
            *ptr++ = '.';
            if (masks.sign & WINED3DSP_WRITEMASK_0)
                *ptr++ = 'x';
            if (masks.sign & WINED3DSP_WRITEMASK_1)
                *ptr++ = 'y';
            if (masks.sign & WINED3DSP_WRITEMASK_2)
                *ptr++ = 'z';
            if (masks.sign & WINED3DSP_WRITEMASK_3)
                *ptr++ = 'w';
        }
        *ptr = '\0';

        shader_addline(buffer, "MAD %s%s, %s, %s, -%s;\n", dst, reg_mask, sign_fixup_src, two, one);
    }
}