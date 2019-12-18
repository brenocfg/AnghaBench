#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ opengl_tex_converter_t ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_2__ converter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_decoder_device_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    opengl_tex_converter_t *tc = (void *)obj;
    converter_sys_t *p_sys = tc->priv;
    vlc_decoder_device_Release(p_sys->device);
}