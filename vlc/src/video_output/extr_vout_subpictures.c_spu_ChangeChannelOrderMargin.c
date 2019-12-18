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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ spu_t ;
struct TYPE_5__ {int margin; int secondary_margin; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ spu_private_t ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;

/* Variables and functions */
#define  VLC_VOUT_ORDER_PRIMARY 129 
#define  VLC_VOUT_ORDER_SECONDARY 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void spu_ChangeChannelOrderMargin(spu_t *spu, enum vlc_vout_order order,
                                  int margin)
{
    spu_private_t *sys = spu->p;

    vlc_mutex_lock(&sys->lock);
    switch (order)
    {
        case VLC_VOUT_ORDER_PRIMARY:
            sys->margin = margin;
            break;
        case VLC_VOUT_ORDER_SECONDARY:
            sys->secondary_margin = margin;
            break;
        default:
            vlc_assert_unreachable();
    }
    vlc_mutex_unlock(&sys->lock);
}