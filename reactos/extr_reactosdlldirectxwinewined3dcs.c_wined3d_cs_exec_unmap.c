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
struct wined3d_resource {TYPE_1__* resource_ops; } ;
struct wined3d_cs_unmap {int /*<<< orphan*/  sub_resource_idx; int /*<<< orphan*/ * hr; struct wined3d_resource* resource; } ;
struct wined3d_cs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resource_sub_resource_unmap ) (struct wined3d_resource*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_unmap(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_unmap *op = data;
    struct wined3d_resource *resource = op->resource;

    *op->hr = resource->resource_ops->resource_sub_resource_unmap(resource, op->sub_resource_idx);
}