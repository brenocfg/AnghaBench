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
struct TYPE_4__ {int /*<<< orphan*/  (* video_mixer_get_feature_enables ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpVideoMixerFeature ;
typedef  int /*<<< orphan*/  VdpVideoMixer ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpBool ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_MIXER_GET_FEATURE_ENABLES ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

VdpStatus vdp_video_mixer_get_feature_enables(const vdp_t *vdp,
    VdpVideoMixer mixer, uint32_t count, const VdpVideoMixerFeature *ids,
    VdpBool *values)
{
    CHECK_FUNC(VIDEO_MIXER_GET_FEATURE_ENABLES);
    return vdp->vt.video_mixer_get_feature_enables(mixer, count, ids, values);
}