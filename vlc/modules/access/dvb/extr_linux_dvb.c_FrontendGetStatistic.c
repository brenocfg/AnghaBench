#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_last_status; } ;
typedef  TYPE_1__ frontend_t ;
struct TYPE_8__ {int i_ber; int i_signal_strenth; int i_snr; } ;
typedef  TYPE_2__ frontend_statistic_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_frontend_handle; TYPE_1__* p_frontend; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_READ_BER ; 
 int /*<<< orphan*/  FE_READ_SIGNAL_STRENGTH ; 
 int /*<<< orphan*/  FE_READ_SNR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int FrontendGetStatistic( dvb_sys_t *p_sys, frontend_statistic_t *p_stat )
{
    frontend_t * p_frontend = p_sys->p_frontend;

    if( (p_frontend->i_last_status & FE_HAS_LOCK) == 0 )
        return VLC_EGENERIC;

    memset( p_stat, 0, sizeof(*p_stat) );
    if( ioctl( p_sys->i_frontend_handle, FE_READ_BER, &p_stat->i_ber ) < 0 )
        p_stat->i_ber = -1;
    if( ioctl( p_sys->i_frontend_handle, FE_READ_SIGNAL_STRENGTH, &p_stat->i_signal_strenth ) < 0 )
        p_stat->i_signal_strenth = -1;
    if( ioctl( p_sys->i_frontend_handle, FE_READ_SNR, &p_stat->i_snr ) < 0 )
        p_stat->i_snr = -1;

    return VLC_SUCCESS;
}