#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_19__ ;
typedef  struct TYPE_41__   TYPE_15__ ;
typedef  struct TYPE_40__   TYPE_14__ ;
typedef  struct TYPE_39__   TYPE_13__ ;
typedef  struct TYPE_38__   TYPE_12__ ;
typedef  struct TYPE_37__   TYPE_11__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
struct TYPE_49__ {int b_present; scalar_t__ i_event; TYPE_5__* p_current; } ;
typedef  TYPE_7__ vlc_epg_t ;
typedef  int uint16_t ;
struct TYPE_50__ {TYPE_9__* p_ctx; TYPE_1__* handle; } ;
typedef  TYPE_8__ ts_psip_t ;
struct TYPE_51__ {int i_tabletype; scalar_t__ p_a65; TYPE_2__* p_stt; int /*<<< orphan*/  p_mgt; int /*<<< orphan*/  p_vct; } ;
typedef  TYPE_9__ ts_psip_context_t ;
struct TYPE_46__ {int /*<<< orphan*/  i_event_length; int /*<<< orphan*/  i_event_start; } ;
struct TYPE_36__ {TYPE_4__ eit; } ;
typedef  TYPE_10__ ts_pmt_t ;
struct TYPE_48__ {TYPE_8__* p_psip; } ;
struct TYPE_37__ {scalar_t__ type; TYPE_6__ u; } ;
typedef  TYPE_11__ ts_pid_t ;
typedef  int /*<<< orphan*/  ts_pat_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  dvbpsi_atsc_ett_t ;
struct TYPE_38__ {int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_source_id; TYPE_13__* p_first_event; int /*<<< orphan*/  b_current_next; } ;
typedef  TYPE_12__ dvbpsi_atsc_eit_t ;
struct TYPE_39__ {scalar_t__ i_length_seconds; int /*<<< orphan*/  i_event_id; struct TYPE_39__* p_next; } ;
typedef  TYPE_13__ dvbpsi_atsc_eit_event_t ;
struct TYPE_40__ {int /*<<< orphan*/  out; TYPE_15__* p_sys; } ;
typedef  TYPE_14__ demux_t ;
struct TYPE_41__ {int /*<<< orphan*/  pids; } ;
typedef  TYPE_15__ demux_sys_t ;
struct TYPE_47__ {int /*<<< orphan*/  i_duration; int /*<<< orphan*/  i_start; } ;
struct TYPE_45__ {int /*<<< orphan*/ * p_pat; } ;
struct TYPE_44__ {int /*<<< orphan*/  i_gps_utc_offset; int /*<<< orphan*/  i_system_time; } ;
struct TYPE_43__ {scalar_t__ p_sys; } ;
struct TYPE_42__ {TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ ATSC_AddVLCEPGEvent (TYPE_14__*,TYPE_9__*,TYPE_13__ const*,int /*<<< orphan*/  const*,TYPE_7__*) ; 
 int /*<<< orphan*/  ATSC_BASE_PID ; 
 int /*<<< orphan*/  ATSC_EITInsert (TYPE_9__*,TYPE_12__*) ; 
 int /*<<< orphan*/ * ATSC_ETTFindByETMId (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* ATSC_GetSiblingxTTPID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int const ATSC_TABLE_TYPE_EIT_0 ; 
 int /*<<< orphan*/  ATSC_TranslateVChannelToProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  EIT_DEBUG_TIMESHIFT (scalar_t__) ; 
 int /*<<< orphan*/  ES_OUT_SET_GROUP_EPG ; 
 TYPE_11__* GetPID (TYPE_15__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PSIP ; 
 int /*<<< orphan*/  assert (int const) ; 
 scalar_t__ atsc_a65_GPSTimeToEpoch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atsc_a65_handle_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvbpsi_atsc_DeleteEIT (TYPE_12__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_7__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_14__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toETMId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* ts_pat_Get_pmt (int /*<<< orphan*/ *,int) ; 
 TYPE_19__* ts_pid_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_epg_Delete (TYPE_7__*) ; 
 TYPE_7__* vlc_epg_New (int const,int) ; 
 int /*<<< orphan*/  vlc_epg_SetCurrent (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static void ATSC_EIT_Callback( void *p_pid, dvbpsi_atsc_eit_t* p_eit )
{
    ts_pid_t *p_eit_pid = (ts_pid_t *) p_pid;
    if( unlikely(p_eit_pid->type != TYPE_PSIP) )
    {
        assert( p_eit_pid->type == TYPE_PSIP );
        dvbpsi_atsc_DeleteEIT( p_eit );
        return;
    }

    demux_t *p_demux = (demux_t *) p_eit_pid->u.p_psip->handle->p_sys;
    demux_sys_t *p_sys = p_demux->p_sys;
    ts_pid_t *p_base_pid = GetPID(p_sys, ATSC_BASE_PID);
    ts_psip_t *p_basepsip = p_base_pid->u.p_psip;
    ts_psip_context_t *p_basectx = p_basepsip->p_ctx;

    if( !p_eit->b_current_next ||
        unlikely(p_base_pid->type != TYPE_PSIP || !p_basectx->p_stt || !p_basectx->p_vct) )
    {
        dvbpsi_atsc_DeleteEIT( p_eit );
        return;
    }

    uint16_t i_program_number;
    if ( !ATSC_TranslateVChannelToProgram( p_basectx->p_vct, p_eit->i_source_id, &i_program_number ) )
    {
        msg_Warn( p_demux, "Received EIT for unknown channel %d", p_eit->i_source_id );
        dvbpsi_atsc_DeleteEIT( p_eit );
        return;
    }

    const ts_pid_t *pid_sibling_ett = ATSC_GetSiblingxTTPID( &p_sys->pids, p_basectx->p_mgt,
                                                     p_eit_pid->u.p_psip );

    /* Get System Time for finding and setting current event */
    time_t i_current_time = atsc_a65_GPSTimeToEpoch( p_basectx->p_stt->i_system_time,
                                                     p_basectx->p_stt->i_gps_utc_offset );
    EIT_DEBUG_TIMESHIFT( i_current_time );

    const uint16_t i_table_type = p_eit_pid->u.p_psip->p_ctx->i_tabletype;
    assert(i_table_type);

    /* Use PID for segmenting our EPG tables updates. 1 EIT/PID transmits 3 hours,
     * with a max of 16 days over 128 EIT/PID. Unlike DVD, table ID is here fixed.
     * see ATSC A/65 5.0 */
    vlc_epg_t *p_epg = vlc_epg_New( i_table_type - ATSC_TABLE_TYPE_EIT_0,
                                    i_program_number );
    if( !p_epg )
    {
        dvbpsi_atsc_DeleteEIT( p_eit );
        return;
    }

    /* Use first table as present/following (not split like DVB) */
    p_epg->b_present = (i_table_type == ATSC_TABLE_TYPE_EIT_0);

    if( !p_basectx->p_a65 && !(p_basectx->p_a65 = atsc_a65_handle_New( NULL )) )
        goto end;

    time_t i_current_event_start_time = 0;
    for( const dvbpsi_atsc_eit_event_t *p_evt = p_eit->p_first_event;
                                        p_evt ; p_evt = p_evt->p_next )
    {
        /* Try to match ETT */
        const dvbpsi_atsc_ett_t *p_ett = NULL;
        if( pid_sibling_ett )
            p_ett = ATSC_ETTFindByETMId( pid_sibling_ett->u.p_psip->p_ctx,
                                         toETMId( p_eit->i_source_id, p_evt->i_event_id ),
                                         p_eit->i_version );

        /* Add Event to EPG based on EIT / available ETT */
        time_t i_start = ATSC_AddVLCEPGEvent( p_demux, p_basectx, p_evt, p_ett, p_epg );

        /* Try to find current event */
        if( i_start <= i_current_time && i_start + p_evt->i_length_seconds > i_current_time )
            i_current_event_start_time = i_start;
    }

    /* Update epg current time from system time ( required for pruning ) */
    if( p_epg->b_present && i_current_event_start_time )
    {
        vlc_epg_SetCurrent( p_epg, i_current_event_start_time );
        ts_pat_t *p_pat = ts_pid_Get(&p_sys->pids, 0)->u.p_pat;
        ts_pmt_t *p_pmt = ts_pat_Get_pmt(p_pat, i_program_number);
        if(p_pmt)
        {
            p_pmt->eit.i_event_start = p_epg->p_current->i_start;
            p_pmt->eit.i_event_length = p_epg->p_current->i_duration;
        }
    }

    if( p_epg->i_event > 0 )
        es_out_Control( p_demux->out, ES_OUT_SET_GROUP_EPG, (int)i_program_number, p_epg );

end:
    vlc_epg_Delete( p_epg );
    ATSC_EITInsert( p_eit_pid->u.p_psip->p_ctx, p_eit );
}