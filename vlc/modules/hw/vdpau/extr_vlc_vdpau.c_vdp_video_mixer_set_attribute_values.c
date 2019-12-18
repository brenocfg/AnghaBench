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
struct TYPE_4__ {int /*<<< orphan*/  (* video_mixer_set_attribute_values ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,void const* const*) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpVideoMixerAttribute ;
typedef  int /*<<< orphan*/  VdpVideoMixer ;
typedef  int /*<<< orphan*/  VdpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_MIXER_SET_ATTRIBUTE_VALUES ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,void const* const*) ; 

VdpStatus vdp_video_mixer_set_attribute_values(const vdp_t *vdp,
    VdpVideoMixer mixer, uint32_t count,
    const VdpVideoMixerAttribute *const ids, const void *const *values)
{
    CHECK_FUNC(VIDEO_MIXER_SET_ATTRIBUTE_VALUES);
    return vdp->vt.video_mixer_set_attribute_values(mixer, count, ids, values);
}