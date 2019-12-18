#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_6__* p_stt; } ;
typedef  TYPE_3__ ts_psip_context_t ;
struct TYPE_16__ {TYPE_1__* p_psip; } ;
struct TYPE_18__ {scalar_t__ type; scalar_t__ i_pid; TYPE_2__ u; } ;
typedef  TYPE_4__ ts_pid_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_19__ {scalar_t__ p_sys; } ;
typedef  TYPE_5__ dvbpsi_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_gps_utc_offset; int /*<<< orphan*/  i_system_time; } ;
typedef  TYPE_6__ dvbpsi_atsc_stt_t ;
struct TYPE_21__ {int /*<<< orphan*/  out; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ demux_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_network_time; int /*<<< orphan*/  i_network_time_update; } ;
typedef  TYPE_8__ demux_sys_t ;
struct TYPE_15__ {TYPE_5__* handle; TYPE_3__* p_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSC_ATTACH (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 scalar_t__ ATSC_BASE_PID ; 
 int /*<<< orphan*/  ATSC_Detach_Dvbpsi_Decoders (TYPE_5__*) ; 
 int /*<<< orphan*/  ATSC_MGT_TABLE_ID ; 
 int /*<<< orphan*/  EIT_DEBUG_TIMESHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_OUT_SET_EPG_TIME ; 
 int /*<<< orphan*/  MGT ; 
 scalar_t__ TYPE_PSIP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atsc_a65_GPSTimeToEpoch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_atsc_DeleteSTT (TYPE_6__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_7__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ATSC_STT_Callback( void *p_cb_basepid, dvbpsi_atsc_stt_t* p_stt )
{
    ts_pid_t *p_base_pid = (ts_pid_t *) p_cb_basepid;
    if( unlikely(p_base_pid->type != TYPE_PSIP || p_base_pid->i_pid != ATSC_BASE_PID) )
    {
        assert( p_base_pid->type == TYPE_PSIP );
        assert( p_base_pid->i_pid == ATSC_BASE_PID );
        dvbpsi_atsc_DeleteSTT( p_stt );
        return;
    }
    demux_t *p_demux = (demux_t *) p_base_pid->u.p_psip->handle->p_sys;
    demux_sys_t *p_sys = p_demux->p_sys;
    ts_psip_context_t *p_ctx = p_base_pid->u.p_psip->p_ctx;
    dvbpsi_t *p_handle = p_base_pid->u.p_psip->handle;

    if( !p_ctx->p_stt ) /* First call */
    {
        if( !ATSC_ATTACH( p_handle, MGT, ATSC_MGT_TABLE_ID, 0x00, p_base_pid ) )
        {
            msg_Err( p_demux, "Can't attach MGT decoder to pid %d", ATSC_BASE_PID );
            ATSC_Detach_Dvbpsi_Decoders( p_handle );
            dvbpsi_atsc_DeleteSTT( p_ctx->p_stt );
            p_stt = NULL;
        }
    }
    else
    {
        dvbpsi_atsc_DeleteSTT( p_ctx->p_stt );
    }

    if( p_stt )
    {
        time_t i_current_time = atsc_a65_GPSTimeToEpoch( p_stt->i_system_time,
                                                         p_stt->i_gps_utc_offset );
        EIT_DEBUG_TIMESHIFT( i_current_time );
        p_sys->i_network_time =  i_current_time;
        p_sys->i_network_time_update = time(NULL);

        es_out_Control( p_demux->out, ES_OUT_SET_EPG_TIME, p_sys->i_network_time );
    }

    p_ctx->p_stt = p_stt;
}