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
struct dmx_region_t {int /*<<< orphan*/  resource; int /*<<< orphan*/  element; } ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dmx_region_t*) ; 
 int /*<<< orphan*/  vc_dispmanx_element_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmx_region_delete(struct dmx_region_t *dmx_region,
                DISPMANX_UPDATE_HANDLE_T update)
{
    vc_dispmanx_element_remove(update, dmx_region->element);
    vc_dispmanx_resource_delete(dmx_region->resource);
    free(dmx_region);
}