#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* video_mixer_render ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
typedef  int /*<<< orphan*/  VdpVideoMixerPictureStructure ;
typedef  int /*<<< orphan*/  VdpVideoMixer ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpRect ;
typedef  int /*<<< orphan*/  VdpOutputSurface ;
typedef  int /*<<< orphan*/  VdpLayer ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_MIXER_RENDER ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

VdpStatus vdp_video_mixer_render(const vdp_t *vdp, VdpVideoMixer mixer,
    VdpOutputSurface bgsurface, const VdpRect *bgrect,
    VdpVideoMixerPictureStructure pic_struct, uint32_t prev_count,
    const VdpVideoSurface *prev, VdpVideoSurface cur, uint32_t next_count,
    const VdpVideoSurface *next, const VdpRect *src_rect,
    VdpOutputSurface dst, const VdpRect *dst_rect, const VdpRect *dst_v_rect,
    uint32_t layerc, const VdpLayer *layerv)
{
    CHECK_FUNC(VIDEO_MIXER_RENDER);
    return vdp->vt.video_mixer_render(mixer, bgsurface, bgrect, pic_struct,
        prev_count, prev, cur, next_count, next, src_rect, dst, dst_rect,
        dst_v_rect, layerc, layerv);
}