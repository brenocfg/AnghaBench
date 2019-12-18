#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_15__ ;
typedef  struct TYPE_40__   TYPE_13__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
struct TYPE_47__ {int /*<<< orphan*/  i_id; } ;
typedef  TYPE_6__ vlc_epg_event_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_48__ {TYPE_8__* p_ctx; TYPE_1__* handle; } ;
typedef  TYPE_7__ ts_psip_t ;
struct TYPE_49__ {int /*<<< orphan*/  p_vct; } ;
typedef  TYPE_8__ ts_psip_context_t ;
struct TYPE_46__ {TYPE_7__* p_psip; } ;
struct TYPE_50__ {scalar_t__ type; TYPE_5__ u; } ;
typedef  TYPE_9__ ts_pid_t ;
typedef  int /*<<< orphan*/  dvbpsi_atsc_mgt_t ;
struct TYPE_37__ {int i_etm_id; int /*<<< orphan*/  i_version; } ;
typedef  TYPE_10__ dvbpsi_atsc_ett_t ;
struct TYPE_38__ {int /*<<< orphan*/  i_event_id; } ;
typedef  TYPE_11__ dvbpsi_atsc_eit_event_t ;
struct TYPE_39__ {int /*<<< orphan*/  out; TYPE_13__* p_sys; } ;
typedef  TYPE_12__ demux_t ;
struct TYPE_40__ {int /*<<< orphan*/  pids; } ;
typedef  TYPE_13__ demux_sys_t ;
struct TYPE_45__ {TYPE_3__* p_psip; } ;
struct TYPE_44__ {TYPE_2__* p_ctx; } ;
struct TYPE_43__ {int /*<<< orphan*/ * p_mgt; } ;
struct TYPE_42__ {scalar_t__ p_sys; } ;
struct TYPE_41__ {TYPE_4__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSC_BASE_PID ; 
 int /*<<< orphan*/  ATSC_CleanETTByChannelVersion (TYPE_8__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__* ATSC_CreateVLCEPGEvent (TYPE_12__*,TYPE_8__*,TYPE_11__ const*,TYPE_10__*) ; 
 int /*<<< orphan*/ * ATSC_ETTFindByETMId (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 TYPE_11__* ATSC_EventFindByETMId (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 TYPE_9__* ATSC_GetSiblingxTTPID (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_7__*) ; 
 int /*<<< orphan*/  ATSC_InsertETTOrdered (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ATSC_TranslateVChannelToProgram (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ES_OUT_SET_GROUP_EPG_EVENT ; 
 TYPE_9__* GetPID (TYPE_13__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PSIP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dvbpsi_atsc_DeleteETT (TYPE_10__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 int /*<<< orphan*/  fromETMId (int,scalar_t__*,scalar_t__*) ; 
 scalar_t__ likely (TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_12__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_12__*,char*,scalar_t__) ; 
 TYPE_15__* ts_pid_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_epg_event_Delete (TYPE_6__*) ; 

__attribute__((used)) static void ATSC_ETT_Callback( void *p_pid, dvbpsi_atsc_ett_t *p_ett )
{
    ts_pid_t *p_ett_pid = (ts_pid_t *) p_pid;
    if( unlikely(p_ett_pid->type != TYPE_PSIP) )
    {
        assert( p_ett_pid->type == TYPE_PSIP );
        dvbpsi_atsc_DeleteETT( p_ett );
        return;
    }

    demux_t *p_demux = (demux_t *) p_ett_pid->u.p_psip->handle->p_sys;
    demux_sys_t *p_sys = p_demux->p_sys;
    ts_pid_t *p_base_pid = GetPID(p_sys, ATSC_BASE_PID);
    ts_psip_t *p_basepsip = p_base_pid->u.p_psip;
    ts_psip_context_t *p_basectx = p_basepsip->p_ctx;

    if( p_ett->i_etm_id & 0x02 ) /* Event ETT */
    {
        ts_psip_context_t *p_ctx = p_ett_pid->u.p_psip->p_ctx;
        uint16_t i_vchannel_id, i_event_id;
        fromETMId( p_ett->i_etm_id, &i_vchannel_id, &i_event_id );

        uint16_t i_program_number;
        if ( !ATSC_TranslateVChannelToProgram( p_basectx->p_vct, i_vchannel_id, &i_program_number ) )
        {
            msg_Warn( p_demux, "Received EIT for unknown channel %d", i_vchannel_id );
            dvbpsi_atsc_DeleteETT( p_ett );
            return;
        }

        /* If ETT with that version isn't already in list (inserted when matched eit is present) */
        if( ATSC_ETTFindByETMId( p_ctx, p_ett->i_etm_id, p_ett->i_version ) == NULL )
        {
            const dvbpsi_atsc_mgt_t *p_mgt = ts_pid_Get( &p_sys->pids, ATSC_BASE_PID )->u.p_psip->p_ctx->p_mgt;
            ts_pid_t *p_sibling_eit = ATSC_GetSiblingxTTPID( &p_sys->pids, p_mgt, p_ett_pid->u.p_psip );
            if( p_sibling_eit )
            {
                const dvbpsi_atsc_eit_event_t *p_event =
                        ATSC_EventFindByETMId( p_sibling_eit->u.p_psip->p_ctx, p_ett->i_etm_id, p_ett->i_version );
                if( p_event )
                {
#ifdef ATSC_DEBUG_EIT
                    msg_Dbg( p_demux, "Should update EIT %x (matched EIT)", p_event->i_event_id );
#endif
                    vlc_epg_event_t *p_evt = ATSC_CreateVLCEPGEvent( p_demux, p_basectx, p_event, p_ett );
                    if( likely(p_evt) )
                    {
                        es_out_Control( p_demux->out, ES_OUT_SET_GROUP_EPG_EVENT,
                                        (int)i_program_number, p_evt );
#ifdef ATSC_DEBUG_EIT
                        msg_Dbg( p_demux, "Updated event %x with ETT", p_evt->i_id );
#endif
                        vlc_epg_event_Delete( p_evt );
                    }
                }
                /* Insert to avoid duplicated event, and to be available to EIT if didn't appear yet */
                ATSC_InsertETTOrdered( p_ctx, p_ett );
                ATSC_CleanETTByChannelVersion( p_ctx, i_vchannel_id, p_ett->i_version );
                return;
            }
        }
    }
    dvbpsi_atsc_DeleteETT( p_ett );
}