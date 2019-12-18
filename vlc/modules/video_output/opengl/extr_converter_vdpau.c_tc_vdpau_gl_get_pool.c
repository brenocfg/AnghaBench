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
typedef  int /*<<< orphan*/  vlc_decoder_device ;
typedef  int /*<<< orphan*/  picture_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  fmt; TYPE_2__* priv; } ;
typedef  TYPE_1__ opengl_tex_converter_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dec_device; } ;
typedef  TYPE_2__ converter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetVDPAUOpaqueDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VDP_RGBA_FORMAT_B8G8R8A8 ; 
 int /*<<< orphan*/ * vlc_vdp_output_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static picture_pool_t *
tc_vdpau_gl_get_pool(opengl_tex_converter_t const *tc,
                     unsigned int requested_count)
{
    converter_sys_t *sys = tc->priv;
    vlc_decoder_device *dec_device = sys->dec_device;
    return vlc_vdp_output_pool_create(GetVDPAUOpaqueDevice(dec_device),
                                      VDP_RGBA_FORMAT_B8G8R8A8,
                                      &tc->fmt, requested_count);
}