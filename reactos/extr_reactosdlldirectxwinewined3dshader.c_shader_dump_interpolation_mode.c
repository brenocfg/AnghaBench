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
typedef  enum wined3d_shader_interpolation_mode { ____Placeholder_wined3d_shader_interpolation_mode } wined3d_shader_interpolation_mode ;

/* Variables and functions */
#define  WINED3DSIM_CONSTANT 134 
#define  WINED3DSIM_LINEAR 133 
#define  WINED3DSIM_LINEAR_CENTROID 132 
#define  WINED3DSIM_LINEAR_NOPERSPECTIVE 131 
#define  WINED3DSIM_LINEAR_NOPERSPECTIVE_CENTROID 130 
#define  WINED3DSIM_LINEAR_NOPERSPECTIVE_SAMPLE 129 
#define  WINED3DSIM_LINEAR_SAMPLE 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_interpolation_mode(struct wined3d_string_buffer *buffer,
        enum wined3d_shader_interpolation_mode interpolation_mode)
{
    switch (interpolation_mode)
    {
        case WINED3DSIM_CONSTANT:
            shader_addline(buffer, "constant");
            break;
        case WINED3DSIM_LINEAR:
            shader_addline(buffer, "linear");
            break;
        case WINED3DSIM_LINEAR_CENTROID:
            shader_addline(buffer, "linear centroid");
            break;
        case WINED3DSIM_LINEAR_NOPERSPECTIVE:
            shader_addline(buffer, "linear noperspective");
            break;
        case WINED3DSIM_LINEAR_SAMPLE:
            shader_addline(buffer, "linear sample");
            break;
        case WINED3DSIM_LINEAR_NOPERSPECTIVE_CENTROID:
            shader_addline(buffer, "linear noperspective centroid");
            break;
        case WINED3DSIM_LINEAR_NOPERSPECTIVE_SAMPLE:
            shader_addline(buffer, "linear noperspective sample");
            break;
        default:
            shader_addline(buffer, "<unrecognized_interpolation_mode %#x>", interpolation_mode);
            break;
    }
}