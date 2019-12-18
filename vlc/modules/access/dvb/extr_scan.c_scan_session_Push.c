#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {scalar_t__ p_nit; scalar_t__ p_sdt; scalar_t__ p_pat; } ;
struct TYPE_11__ {TYPE_1__ local; scalar_t__ b_use_nit; TYPE_4__* p_nithandle; scalar_t__ p_obj; TYPE_4__* p_sdthandle; TYPE_4__* p_pathandle; } ;
typedef  TYPE_2__ scan_session_t ;
typedef  int /*<<< orphan*/  dvbpsi_pat_callback ;
typedef  int /*<<< orphan*/  dvbpsi_demux_new_cb_t ;
struct TYPE_12__ {void* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVBPSI_MSG_DEBUG ; 
 scalar_t__ PATCallBack ; 
 scalar_t__ PSINewTableCallBack ; 
 int const PSI_PAT_PID ; 
 int const SI_NIT_PID ; 
 int const SI_SDT_PID ; 
 int /*<<< orphan*/  dvbpsi_AttachDemux (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dvbpsi_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  dvbpsi_messages ; 
 void* dvbpsi_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_packet_push (TYPE_4__*,int const*) ; 
 int /*<<< orphan*/  dvbpsi_pat_attach (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static bool scan_session_Push( scan_session_t *p_scan, const uint8_t *p_packet )
{
    if( p_packet[0] != 0x47 )
        return false;

    /* */
    const int i_pid = ( (p_packet[1]&0x1f)<<8) | p_packet[2];
    if( i_pid == PSI_PAT_PID )
    {
        if( !p_scan->p_pathandle )
        {
            p_scan->p_pathandle = dvbpsi_new( &dvbpsi_messages, DVBPSI_MSG_DEBUG );
            if( !p_scan->p_pathandle )
                return false;

            p_scan->p_pathandle->p_sys = (void *) p_scan->p_obj;
            if( !dvbpsi_pat_attach( p_scan->p_pathandle, (dvbpsi_pat_callback)PATCallBack, p_scan ) )
            {
                dvbpsi_delete( p_scan->p_pathandle );
                p_scan->p_pathandle = NULL;
                return false;
            }
        }
        if( p_scan->p_pathandle )
            dvbpsi_packet_push( p_scan->p_pathandle, p_packet );
    }
    else if( i_pid == SI_SDT_PID )
    {
        if( !p_scan->p_sdthandle )
        {
            p_scan->p_sdthandle = dvbpsi_new( &dvbpsi_messages, DVBPSI_MSG_DEBUG );
            if( !p_scan->p_sdthandle )
                return false;

            p_scan->p_sdthandle->p_sys = (void *) p_scan->p_obj;
            if( !dvbpsi_AttachDemux( p_scan->p_sdthandle, (dvbpsi_demux_new_cb_t)PSINewTableCallBack, p_scan ) )
            {
                dvbpsi_delete( p_scan->p_sdthandle );
                p_scan->p_sdthandle = NULL;
                return false;
            }
        }

        if( p_scan->p_sdthandle )
            dvbpsi_packet_push( p_scan->p_sdthandle, p_packet );
    }
    else if( p_scan->b_use_nit && i_pid == SI_NIT_PID ) /*if( i_pid == p_scan->i_nit_pid )*/
    {
        if( !p_scan->p_nithandle )
        {
            p_scan->p_nithandle = dvbpsi_new( &dvbpsi_messages, DVBPSI_MSG_DEBUG );
            if( !p_scan->p_nithandle )
                return false;

            p_scan->p_nithandle->p_sys = (void *) p_scan->p_obj;
            if( !dvbpsi_AttachDemux( p_scan->p_nithandle, (dvbpsi_demux_new_cb_t)PSINewTableCallBack, p_scan ) )
            {
                dvbpsi_delete( p_scan->p_nithandle );
                p_scan->p_nithandle = NULL;
                return false;
            }
        }
        if( p_scan->p_nithandle )
            dvbpsi_packet_push( p_scan->p_nithandle, p_packet );
    }

    return p_scan->local.p_pat && p_scan->local.p_sdt &&
            (!p_scan->b_use_nit || p_scan->local.p_nit);
}