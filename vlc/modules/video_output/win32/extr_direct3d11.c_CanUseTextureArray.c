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
struct TYPE_6__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct wddm_version {int wddm; int revision; } ;
struct TYPE_5__ {int /*<<< orphan*/  d3d_dev; } ;

/* Variables and functions */
 scalar_t__ D3D11CheckDriverVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wddm_version*) ; 
 int /*<<< orphan*/  GPU_MANUFACTURER_AMD ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static bool CanUseTextureArray(vout_display_t *vd)
{
#ifndef HAVE_ID3D11VIDEODECODER
    (void) vd;
    return false;
#else
    // 15.200.1062.1004 is wrong - 2015/08/03 - 15.7.1 WHQL
    // 21.19.144.1281 is wrong   -
    // 22.19.165.3 is good       - 2017/05/04 - ReLive Edition 17.5.1
    struct wddm_version WDDM_os = {
        .wddm         = 21,  // starting with drivers designed for W10 Anniversary Update
    };
    if (D3D11CheckDriverVersion(&vd->sys->d3d_dev, GPU_MANUFACTURER_AMD, &WDDM_os) != VLC_SUCCESS)
    {
        msg_Dbg(vd, "AMD driver too old, fallback to legacy shader mode");
        return false;
    }

    // xx.xx.1000.xxx drivers can't happen here for WDDM > 2.0
    struct wddm_version WDDM_build = {
        .revision     = 162,
    };
    if (D3D11CheckDriverVersion(&vd->sys->d3d_dev, GPU_MANUFACTURER_AMD, &WDDM_build) != VLC_SUCCESS)
    {
        msg_Dbg(vd, "Bogus AMD driver detected, fallback to legacy shader mode");
        return false;
    }

    return true;
#endif
}