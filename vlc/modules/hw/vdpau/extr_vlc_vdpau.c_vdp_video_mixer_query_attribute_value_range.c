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
struct TYPE_4__ {int /*<<< orphan*/  (* video_mixer_query_attribute_value_range ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  VdpVideoMixerAttribute ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_MIXER_QUERY_ATTRIBUTE_VALUE_RANGE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 

VdpStatus vdp_video_mixer_query_attribute_value_range(const vdp_t *vdp,
    VdpDevice device, VdpVideoMixerAttribute attribute, void *min, void *max)
{
    CHECK_FUNC(VIDEO_MIXER_QUERY_ATTRIBUTE_VALUE_RANGE);
    return vdp->vt.video_mixer_query_attribute_value_range(device, attribute,
        min, max);
}