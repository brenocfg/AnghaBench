#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* sys; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_2__ vout_display_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  d3d_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * Direct3D9CreatePicturePool (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 

__attribute__((used)) static picture_pool_t *DisplayPool(vout_display_t *vd, unsigned count)
{
    if ( vd->sys->pool == NULL )
    {
        vd->sys->pool = Direct3D9CreatePicturePool(VLC_OBJECT(vd), &vd->sys->d3d_dev,
                                                   &vd->fmt, count);
    }
    return vd->sys->pool;
}