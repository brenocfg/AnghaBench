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
struct wined3d_resource {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  texture_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_texture_decref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ULONG texture_resource_decref(struct wined3d_resource *resource)
{
    return wined3d_texture_decref(texture_from_resource(resource));
}