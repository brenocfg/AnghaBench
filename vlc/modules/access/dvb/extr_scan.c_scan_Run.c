#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  scan_tuner_config_t ;
struct TYPE_18__ {scalar_t__ b_use_nit; } ;
struct TYPE_19__ {int (* pf_tune ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* pf_read ) (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *,size_t*) ;int /*<<< orphan*/  p_cbdata; int /*<<< orphan*/  (* pf_stats ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pf_filter ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;TYPE_1__ parameter; } ;
typedef  TYPE_2__ scan_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_snr; } ;
typedef  TYPE_3__ scan_session_t ;
typedef  unsigned int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSI_PAT_PID ; 
 int SCAN_READ_BUFFER_COUNT ; 
 int /*<<< orphan*/  SI_NIT_PID ; 
 int /*<<< orphan*/  SI_SDT_PID ; 
 int TS_PACKET_SIZE ; 
 int VLC_EGENERIC ; 
 int VLC_ENOITEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ scan_Next (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_session_Destroy (TYPE_2__*,TYPE_3__*) ; 
 unsigned int scan_session_GetTablesTimeout (TYPE_3__*) ; 
 TYPE_3__* scan_session_New (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scan_session_Push (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub5 (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 unsigned int vlc_tick_now () ; 

int scan_Run( scan_t *p_scan )
{
    scan_tuner_config_t cfg;
    if( scan_Next( p_scan, &cfg ) )
        return VLC_ENOITEM;

    scan_session_t *session = scan_session_New( p_scan, &cfg );
    if( unlikely(session == NULL) )
        return VLC_EGENERIC;

    if( p_scan->pf_tune( p_scan, p_scan->p_cbdata, &cfg ) != VLC_SUCCESS )
    {
        scan_session_Destroy( p_scan, session );
        return VLC_EGENERIC;
    }

    p_scan->pf_filter( p_scan, p_scan->p_cbdata, PSI_PAT_PID, true );
    p_scan->pf_filter( p_scan, p_scan->p_cbdata, SI_SDT_PID, true );
    if( p_scan->parameter.b_use_nit )
        p_scan->pf_filter( p_scan, p_scan->p_cbdata, SI_NIT_PID, true );

    /* */
    uint8_t packet[TS_PACKET_SIZE * SCAN_READ_BUFFER_COUNT];
    int64_t i_scan_start = vlc_tick_now();

    for( ;; )
    {
        unsigned i_timeout = scan_session_GetTablesTimeout( session );
        vlc_tick_t i_remaining = vlc_tick_now() - i_scan_start;
        if( i_remaining > i_timeout )
            break;

        size_t i_packet_count = 0;
        int i_ret = p_scan->pf_read( p_scan, p_scan->p_cbdata,
                                     i_timeout - i_remaining,
                                     SCAN_READ_BUFFER_COUNT,
                                     (uint8_t *) &packet, &i_packet_count );

        if( p_scan->pf_stats )
            p_scan->pf_stats( p_scan, p_scan->p_cbdata, &session->i_snr );

        if ( i_ret != VLC_SUCCESS )
            break;

        for( size_t i=0; i< i_packet_count; i++ )
        {
            if( scan_session_Push( session,
                                   &packet[i * TS_PACKET_SIZE] ) )
                break;
        }
    }

    scan_session_Destroy( p_scan, session );

    return VLC_SUCCESS;
}