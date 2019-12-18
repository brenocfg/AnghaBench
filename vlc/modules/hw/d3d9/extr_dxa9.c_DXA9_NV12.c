#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_17__ {scalar_t__ i_visible_height; scalar_t__ i_y_offset; } ;
struct TYPE_18__ {TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_19__ {int /*<<< orphan*/  surface; } ;
typedef  TYPE_3__ picture_sys_d3d9_t ;
struct TYPE_20__ {scalar_t__ p_sys; } ;
typedef  TYPE_4__ filter_t ;
typedef  int /*<<< orphan*/  copy_cache_t ;
struct TYPE_22__ {int Pitch; int /*<<< orphan*/  const* pBits; } ;
struct TYPE_21__ {scalar_t__ Format; int Height; } ;
typedef  TYPE_5__ D3DSURFACE_DESC ;
typedef  TYPE_6__ D3DLOCKED_RECT ;

/* Variables and functions */
 TYPE_3__* ActiveD3D9PictureSys (TYPE_2__*) ; 
 int /*<<< orphan*/  Copy420_SP_to_SP (TYPE_2__*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLock (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  IDirect3DSurface9_UnlockRect (int /*<<< orphan*/ ) ; 
 scalar_t__ MAKEFOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  __MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,scalar_t__) ; 

__attribute__((used)) static void DXA9_NV12(filter_t *p_filter, picture_t *src, picture_t *dst)
{
    copy_cache_t *p_copy_cache = (copy_cache_t*) p_filter->p_sys;
    picture_sys_d3d9_t *p_sys = ActiveD3D9PictureSys(src);

    D3DSURFACE_DESC desc;
    D3DLOCKED_RECT lock;
    if (!GetLock(p_filter, p_sys->surface, &lock, &desc))
        return;

    if (desc.Format == MAKEFOURCC('N','V','1','2')
     || desc.Format == MAKEFOURCC('P','0','1','0')) {
        const uint8_t *plane[2] = {
            lock.pBits,
            (uint8_t*)lock.pBits + lock.Pitch * desc.Height
        };
        size_t  pitch[2] = {
            lock.Pitch,
            lock.Pitch,
        };
        Copy420_SP_to_SP(dst, plane, pitch,
                         __MIN(desc.Height, src->format.i_y_offset + src->format.i_visible_height),
                         p_copy_cache);
    } else {
        msg_Err(p_filter, "Unsupported DXA9 conversion from 0x%08X to NV12", desc.Format);
    }

    /* */
    IDirect3DSurface9_UnlockRect(p_sys->surface);
}