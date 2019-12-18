#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ texture; } ;
typedef  TYPE_1__ d3d_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DTexture9_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void Direct3D9DeleteRegions(size_t count, d3d_region_t *region)
{
    for (size_t i = 0; i < count; i++) {
        if (region[i].texture)
            IDirect3DTexture9_Release(region[i].texture);
    }
    free(region);
}