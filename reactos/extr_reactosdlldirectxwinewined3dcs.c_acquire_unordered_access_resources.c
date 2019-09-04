#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_unordered_access_view {int /*<<< orphan*/  resource; } ;
struct TYPE_4__ {TYPE_1__* uav_resource_info; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int MAX_UNORDERED_ACCESS_VIEWS ; 
 int /*<<< orphan*/  wined3d_resource_acquire (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acquire_unordered_access_resources(const struct wined3d_shader *shader,
        struct wined3d_unordered_access_view * const *views)
{
    unsigned int i;

    if (!shader)
        return;

    for (i = 0; i < MAX_UNORDERED_ACCESS_VIEWS; ++i)
    {
        if (!shader->reg_maps.uav_resource_info[i].type)
            continue;

        if (!views[i])
            continue;

        wined3d_resource_acquire(views[i]->resource);
    }
}