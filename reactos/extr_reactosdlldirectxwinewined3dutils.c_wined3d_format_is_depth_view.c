#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
struct TYPE_3__ {int typeless_id; int depth_view_id; } ;
typedef  int BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int FALSE ; 
 TYPE_1__* typeless_depth_stencil_formats ; 

BOOL wined3d_format_is_depth_view(enum wined3d_format_id resource_format_id,
        enum wined3d_format_id view_format_id)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(typeless_depth_stencil_formats); ++i)
    {
        if (typeless_depth_stencil_formats[i].typeless_id == resource_format_id)
            return typeless_depth_stencil_formats[i].depth_view_id == view_format_id;
    }
    return FALSE;
}