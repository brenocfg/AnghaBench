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
struct wined3d_state {struct wined3d_shader** shader; } ;
struct TYPE_4__ {int /*<<< orphan*/  element_count; } ;
struct TYPE_5__ {TYPE_1__ so_desc; } ;
struct TYPE_6__ {TYPE_2__ gs; } ;
struct wined3d_shader {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t WINED3D_SHADER_TYPE_GEOMETRY ; 

__attribute__((used)) static BOOL use_transform_feedback(const struct wined3d_state *state)
{
    const struct wined3d_shader *shader;
    if (!(shader = state->shader[WINED3D_SHADER_TYPE_GEOMETRY]))
        return FALSE;
    return shader->u.gs.so_desc.element_count;
}