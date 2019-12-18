#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
struct TYPE_5__ {TYPE_3__* priv; TYPE_1__* vt; } ;
typedef  TYPE_2__ opengl_tex_converter_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dec_device; } ;
typedef  TYPE_3__ converter_sys_t ;
struct TYPE_4__ {scalar_t__ (* GetError ) () ;} ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GetVDPAUOpaqueDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glVDPAUFiniNV () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Close(vlc_object_t *obj)
{
    opengl_tex_converter_t *tc = (void *)obj;
    _glVDPAUFiniNV(); assert(tc->vt->GetError() == GL_NO_ERROR);
    converter_sys_t *sys = tc->priv;
    vlc_decoder_device *dec_device = sys->dec_device;
    vdp_release_x11(GetVDPAUOpaqueDevice(dec_device));
    vlc_decoder_device_Release(dec_device);
}