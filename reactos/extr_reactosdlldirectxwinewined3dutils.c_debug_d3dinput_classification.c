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
typedef  enum wined3d_input_classification { ____Placeholder_wined3d_input_classification } wined3d_input_classification ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_INPUT_PER_INSTANCE_DATA 129 
#define  WINED3D_INPUT_PER_VERTEX_DATA 128 

const char *debug_d3dinput_classification(enum wined3d_input_classification classification)
{
    switch (classification)
    {
#define WINED3D_TO_STR(x) case x: return #x
        WINED3D_TO_STR(WINED3D_INPUT_PER_VERTEX_DATA);
        WINED3D_TO_STR(WINED3D_INPUT_PER_INSTANCE_DATA);
#undef WINED3D_TO_STR
        default:
            FIXME("Unrecognized input classification %#x.\n", classification);
            return "unrecognized";
    }
}