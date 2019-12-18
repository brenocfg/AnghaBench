#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vlc_va_t ;
struct TYPE_8__ {scalar_t__* hw_surface; int /*<<< orphan*/  va_pool; } ;
typedef  TYPE_2__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  vlc_va_surface_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_3__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/ * NewSurfacePicContext (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int VLC_ENOITEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * va_pool_Get (int /*<<< orphan*/ ) ; 
 size_t va_surface_GetIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  va_surface_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Get(vlc_va_t *va, picture_t *pic, uint8_t **data)
{
    vlc_va_sys_t *sys = va->sys;
    vlc_va_surface_t *va_surface = va_pool_Get(sys->va_pool);
    if (unlikely(va_surface == NULL))
        return VLC_ENOITEM;
    pic->context = NewSurfacePicContext(va, va_surface);
    if (unlikely(pic->context == NULL))
    {
        va_surface_Release(va_surface);
        return VLC_ENOITEM;
    }
    *data = (uint8_t*)sys->hw_surface[va_surface_GetIndex(va_surface)];
    return VLC_SUCCESS;
}