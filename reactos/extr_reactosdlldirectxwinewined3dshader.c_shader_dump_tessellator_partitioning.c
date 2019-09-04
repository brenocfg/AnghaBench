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
typedef  enum wined3d_tessellator_partitioning { ____Placeholder_wined3d_tessellator_partitioning } wined3d_tessellator_partitioning ;

/* Variables and functions */
#define  WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN 131 
#define  WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD 130 
#define  WINED3D_TESSELLATOR_PARTITIONING_INTEGER 129 
#define  WINED3D_TESSELLATOR_PARTITIONING_POW2 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_dump_tessellator_partitioning(struct wined3d_string_buffer *buffer,
        enum wined3d_tessellator_partitioning partitioning)
{
    switch (partitioning)
    {
        case WINED3D_TESSELLATOR_PARTITIONING_INTEGER:
            shader_addline(buffer, "integer");
            break;
        case WINED3D_TESSELLATOR_PARTITIONING_POW2:
            shader_addline(buffer, "pow2");
            break;
        case WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD:
            shader_addline(buffer, "fractional_odd");
            break;
        case WINED3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN:
            shader_addline(buffer, "fractional_even");
            break;
        default:
            shader_addline(buffer, "unknown_tessellator_partitioning(%#x)", partitioning);
            break;
    }
}