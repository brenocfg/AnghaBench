#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  vdp_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;
typedef  int /*<<< orphan*/  VdpRGBAFormat ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 scalar_t__ OutputCheckFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_vdp_output_pool_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static picture_pool_t *OutputPoolAlloc(vlc_object_t *obj, vdp_t *vdp,
    VdpDevice dev, const video_format_t *restrict fmt)
{
    /* Check output surface format */
    VdpRGBAFormat rgb_fmt;

    if (OutputCheckFormat(obj, vdp, dev, fmt, &rgb_fmt))
        return NULL;

    /* Allocate the pool */
    return vlc_vdp_output_pool_create(vdp, rgb_fmt, fmt, 3);
}