#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
struct TYPE_2__ {unsigned int coord_size; } ;
typedef  int BOOL ;

/* Variables and functions */
 int WINED3D_SHADER_RESOURCE_TEXTURE_1DARRAY ; 
 int WINED3D_SHADER_RESOURCE_TEXTURE_2DARRAY ; 
 TYPE_1__* resource_type_info ; 

__attribute__((used)) static void shader_glsl_get_coord_size(enum wined3d_shader_resource_type resource_type,
        unsigned int *coord_size, unsigned int *deriv_size)
{
    const BOOL is_array = resource_type == WINED3D_SHADER_RESOURCE_TEXTURE_1DARRAY
            || resource_type == WINED3D_SHADER_RESOURCE_TEXTURE_2DARRAY;

    *coord_size = resource_type_info[resource_type].coord_size;
    *deriv_size = *coord_size;
    if (is_array)
        --(*deriv_size);
}