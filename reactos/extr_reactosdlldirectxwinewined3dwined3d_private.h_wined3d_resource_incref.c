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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  (* resource_incref ) (struct wined3d_resource*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wined3d_resource*) ; 

__attribute__((used)) static inline ULONG wined3d_resource_incref(struct wined3d_resource *resource)
{
    return resource->resource_ops->resource_incref(resource);
}