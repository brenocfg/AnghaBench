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
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static unsigned int shader_glsl_swizzle_get_component(DWORD swizzle,
        unsigned int component_idx)
{
    /* swizzle bits fields: wwzzyyxx */
    return (swizzle >> (2 * component_idx)) & 0x3;
}