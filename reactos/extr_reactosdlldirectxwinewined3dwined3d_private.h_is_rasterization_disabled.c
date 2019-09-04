#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rasterizer_stream_idx; } ;
struct TYPE_5__ {TYPE_1__ so_desc; } ;
struct TYPE_6__ {TYPE_2__ gs; } ;
struct wined3d_shader {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ WINED3D_NO_RASTERIZER_STREAM ; 

__attribute__((used)) static inline BOOL is_rasterization_disabled(const struct wined3d_shader *geometry_shader)
{
    return geometry_shader
            && geometry_shader->u.gs.so_desc.rasterizer_stream_idx == WINED3D_NO_RASTERIZER_STREAM;
}