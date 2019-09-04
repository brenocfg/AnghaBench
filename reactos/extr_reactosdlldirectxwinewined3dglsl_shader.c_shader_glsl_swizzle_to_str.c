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
typedef  unsigned int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 size_t shader_glsl_swizzle_get_component (unsigned int,unsigned int) ; 

__attribute__((used)) static void shader_glsl_swizzle_to_str(DWORD swizzle, BOOL fixup, DWORD mask, char *str)
{
    /* For registers of type WINED3DDECLTYPE_D3DCOLOR, data is stored as "bgra",
     * but addressed as "rgba". To fix this we need to swap the register's x
     * and z components. */
    const char *swizzle_chars = fixup ? "zyxw" : "xyzw";
    unsigned int i;

    *str++ = '.';
    for (i = 0; i < 4; ++i)
    {
        if (mask & (WINED3DSP_WRITEMASK_0 << i))
            *str++ = swizzle_chars[shader_glsl_swizzle_get_component(swizzle, i)];
    }
    *str = '\0';
}