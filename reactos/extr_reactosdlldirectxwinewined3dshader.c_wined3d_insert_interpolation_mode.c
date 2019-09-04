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
typedef  enum wined3d_shader_interpolation_mode { ____Placeholder_wined3d_shader_interpolation_mode } wined3d_shader_interpolation_mode ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3DSIM_LINEAR_NOPERSPECTIVE_SAMPLE ; 
 unsigned int WINED3D_PACKED_INTERPOLATION_BIT_COUNT ; 
 int /*<<< orphan*/  wined3d_insert_bits (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void wined3d_insert_interpolation_mode(DWORD *packed_interpolation_mode,
        unsigned int register_idx, enum wined3d_shader_interpolation_mode mode)
{
    if (mode > WINED3DSIM_LINEAR_NOPERSPECTIVE_SAMPLE)
        FIXME("Unexpected interpolation mode %#x.\n", mode);

    wined3d_insert_bits(packed_interpolation_mode,
            register_idx * WINED3D_PACKED_INTERPOLATION_BIT_COUNT, WINED3D_PACKED_INTERPOLATION_BIT_COUNT, mode);
}