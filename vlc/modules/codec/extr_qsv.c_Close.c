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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ encoder_t ;
struct TYPE_5__ {scalar_t__ input_pool; int /*<<< orphan*/  packets; int /*<<< orphan*/  session; } ;
typedef  TYPE_2__ encoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFXVideoENCODE_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_task_t_fifo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_pool_Release (scalar_t__) ; 

__attribute__((used)) static void Close(vlc_object_t *this)
{
    encoder_t *enc = (encoder_t *)this;
    encoder_sys_t *sys = enc->p_sys;

    MFXVideoENCODE_Close(sys->session);
    MFXClose(sys->session);
    /* if (enc->fmt_out.p_extra) */
    /*     free(enc->fmt_out.p_extra); */
    async_task_t_fifo_Release(&sys->packets);
    if (sys->input_pool)
        picture_pool_Release(sys->input_pool);
    free(sys);
}