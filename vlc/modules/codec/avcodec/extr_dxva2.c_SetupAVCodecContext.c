#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  workaround; int /*<<< orphan*/  surface; int /*<<< orphan*/ * cfg; } ;
struct TYPE_8__ {TYPE_1__ hw; TYPE_2__* selected_decoder; int /*<<< orphan*/  hw_surface; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_3__ vlc_va_sys_t ;
struct TYPE_9__ {TYPE_1__* hwaccel_context; } ;
struct TYPE_7__ {int /*<<< orphan*/  workaround; } ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */

__attribute__((used)) static void SetupAVCodecContext(void *opaque, AVCodecContext *avctx)
{
    vlc_va_sys_t *sys = opaque;
    sys->hw.cfg = &sys->cfg;
    sys->hw.surface = sys->hw_surface;
    sys->hw.workaround = sys->selected_decoder->workaround;
    avctx->hwaccel_context = &sys->hw;
}