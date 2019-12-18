#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {scalar_t__ i_chroma; } ;
struct TYPE_21__ {scalar_t__ force; } ;
struct TYPE_26__ {TYPE_9__ source; TYPE_1__ obj; TYPE_6__* sys; } ;
typedef  TYPE_5__ vout_display_t ;
struct TYPE_24__ {int i_width; int i_height; } ;
struct TYPE_22__ {TYPE_3__ texture_source; } ;
struct TYPE_25__ {int i_width; int i_height; TYPE_2__* textureFormat; } ;
struct TYPE_27__ {scalar_t__ swapCb; int /*<<< orphan*/  outside_opaque; int /*<<< orphan*/  sys; TYPE_20__ area; TYPE_4__ picQuad; int /*<<< orphan*/  legacy_shader; } ;
typedef  TYPE_6__ vout_display_sys_t ;
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_28__ {scalar_t__ i_chroma; int i_width; int i_height; } ;
typedef  TYPE_7__ video_format_t ;
struct TYPE_23__ {scalar_t__ formatTexture; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommonPlacePicture (int /*<<< orphan*/ ,TYPE_20__*,int /*<<< orphan*/ *) ; 
 scalar_t__ DXGI_FORMAT_B5G6R5_UNORM ; 
 scalar_t__ DXGI_FORMAT_R8G8B8A8_UNORM ; 
 scalar_t__ Direct3D11CreateGenericResources (TYPE_5__*) ; 
 int /*<<< orphan*/  LocalSwapchainCleanupDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ LocalSwapchainSwap ; 
 int QueryDisplayFormat (TYPE_5__*,TYPE_7__*) ; 
 int SetupOutputFormat (TYPE_5__*,TYPE_7__*) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_5__*) ; 
 int VLC_SUCCESS ; 
 scalar_t__ is_d3d11_opaque (scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_7__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_7__*,TYPE_9__*) ; 
 scalar_t__* vlc_fourcc_GetRGBFallback (scalar_t__) ; 
 scalar_t__* vlc_fourcc_GetYUVFallback (scalar_t__) ; 
 scalar_t__ vlc_fourcc_IsYUV (scalar_t__) ; 

__attribute__((used)) static int Direct3D11Open(vout_display_t *vd, video_format_t *fmtp)
{
    vout_display_sys_t *sys = vd->sys;
    video_format_t fmt;
    video_format_Copy(&fmt, &vd->source);
    int err = SetupOutputFormat(vd, &fmt);
    if (err != VLC_SUCCESS)
    {
        if (!is_d3d11_opaque(vd->source.i_chroma)
#if !VLC_WINSTORE_APP
            && vd->obj.force
#endif
                )
        {
            const vlc_fourcc_t *list = vlc_fourcc_IsYUV(vd->source.i_chroma) ?
                        vlc_fourcc_GetYUVFallback(vd->source.i_chroma) :
                        vlc_fourcc_GetRGBFallback(vd->source.i_chroma);
            for (unsigned i = 0; list[i] != 0; i++) {
                fmt.i_chroma = list[i];
                if (fmt.i_chroma == vd->source.i_chroma)
                    continue;
                err = SetupOutputFormat(vd, &fmt);
                if (err == VLC_SUCCESS)
                    break;
            }
        }
        if (err != VLC_SUCCESS)
        {
            if ( sys->swapCb == LocalSwapchainSwap )
                LocalSwapchainCleanupDevice( sys->outside_opaque );
            return err;
        }
    }

    /* adjust the decoder sizes to have proper padding */
    sys->picQuad.i_width  = fmt.i_width;
    sys->picQuad.i_height = fmt.i_height;
    if (!sys->legacy_shader && is_d3d11_opaque(fmt.i_chroma))
    {
        sys->picQuad.i_width  = (sys->picQuad.i_width  + 0x7F) & ~0x7F;
        sys->picQuad.i_height = (sys->picQuad.i_height + 0x7F) & ~0x7F;
    }
    else
    if ( sys->picQuad.textureFormat->formatTexture != DXGI_FORMAT_R8G8B8A8_UNORM &&
         sys->picQuad.textureFormat->formatTexture != DXGI_FORMAT_B5G6R5_UNORM )
    {
        sys->picQuad.i_width  = (sys->picQuad.i_width  + 0x01) & ~0x01;
        sys->picQuad.i_height = (sys->picQuad.i_height + 0x01) & ~0x01;
    }

    sys->area.texture_source.i_width  = sys->picQuad.i_width;
    sys->area.texture_source.i_height = sys->picQuad.i_height;

    CommonPlacePicture(VLC_OBJECT(vd), &sys->area, &sys->sys);

    err = QueryDisplayFormat(vd, &fmt);
    if (err != VLC_SUCCESS) {
        msg_Err(vd, "Could not update the backbuffer");
        return err;
    }

    if (Direct3D11CreateGenericResources(vd)) {
        msg_Err(vd, "Failed to allocate resources");
        if ( sys->swapCb == LocalSwapchainSwap )
            LocalSwapchainCleanupDevice( sys->outside_opaque );
        return VLC_EGENERIC;
    }

    video_format_Clean(fmtp);
    *fmtp = fmt;

    return VLC_SUCCESS;
}