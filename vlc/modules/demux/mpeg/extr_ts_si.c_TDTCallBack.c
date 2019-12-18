#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* p_si; } ;
struct TYPE_15__ {TYPE_3__ u; } ;
typedef  TYPE_4__ ts_pid_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_16__ {int /*<<< orphan*/  i_utc_time; } ;
typedef  TYPE_5__ dvbpsi_tot_t ;
struct TYPE_17__ {int /*<<< orphan*/  out; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ demux_t ;
struct TYPE_18__ {scalar_t__ standard; scalar_t__ i_network_time; int /*<<< orphan*/  pids; int /*<<< orphan*/  i_network_time_update; } ;
typedef  TYPE_7__ demux_sys_t ;
struct TYPE_13__ {TYPE_1__* handle; } ;
struct TYPE_12__ {int /*<<< orphan*/  p_decoder; } ;

/* Variables and functions */
 scalar_t__ EITConvertStartTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_OUT_SET_EPG_TIME ; 
 int /*<<< orphan*/  TS_SI_TDT_PID ; 
 scalar_t__ TS_STANDARD_ARIB ; 
 int /*<<< orphan*/  dvbpsi_decoder_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dvbpsi_tot_delete (TYPE_5__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 TYPE_4__* ts_pid_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TDTCallBack( demux_t *p_demux, dvbpsi_tot_t *p_tdt )
{
    demux_sys_t        *p_sys = p_demux->p_sys;


    p_sys->i_network_time = EITConvertStartTime( p_tdt->i_utc_time );
    p_sys->i_network_time_update = time(NULL);
    if( p_sys->standard == TS_STANDARD_ARIB )
    {
        /* All ARIB-B10 times are in JST time, where DVB is UTC. (spec being a fork)
           DVB TOT should include DTS offset in descriptor 0x58 (including DST),
           but as there's no DST in JAPAN (since Showa 27/1952)
           and considering that no-one seems to send TDT or desc 0x58,
           falling back on fixed offset is safe */
        p_sys->i_network_time += 9 * 3600;
    }

    /* Because libdvbpsi is broken and deduplicating timestamp tables,
     * we need to reset it to get next timestamp callback */
    ts_pid_t *pid = ts_pid_Get( &p_sys->pids, TS_SI_TDT_PID );
    dvbpsi_decoder_reset( pid->u.p_si->handle->p_decoder, true );
    dvbpsi_tot_delete(p_tdt);

    es_out_Control( p_demux->out, ES_OUT_SET_EPG_TIME, (int64_t) p_sys->i_network_time );
}