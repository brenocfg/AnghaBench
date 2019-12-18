#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_download_id; int i_logo_id; } ;
struct TYPE_11__ {scalar_t__ i_event_start; scalar_t__ i_event_length; } ;
struct TYPE_10__ {int b_disable; int i_pcroffset; int b_fix_done; void* i_first_dts; void* i_first; void* i_current; } ;
struct TYPE_9__ {int i_version; int /*<<< orphan*/  objects; } ;
struct TYPE_13__ {int i_version; int i_number; int i_pid_pcr; int b_selected; TYPE_4__ arib; TYPE_3__ eit; TYPE_2__ pcr; int /*<<< orphan*/ * p_si_sdt_pid; int /*<<< orphan*/ * p_atsc_si_basepid; scalar_t__ i_last_dts_byte; void* i_last_dts; TYPE_1__ od; int /*<<< orphan*/ * iod; int /*<<< orphan*/  e_streams; int /*<<< orphan*/  handle; } ;
typedef  TYPE_5__ ts_pmt_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 void* TS_TICK_UNKNOWN ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  handle_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* malloc (int) ; 

ts_pmt_t *ts_pmt_New( demux_t *p_demux )
{
    ts_pmt_t *pmt = malloc( sizeof( ts_pmt_t ) );
    if( !pmt )
        return NULL;

    if( !handle_Init( p_demux, &pmt->handle ) )
    {
        free( pmt );
        return NULL;
    }

    ARRAY_INIT( pmt->e_streams );

    pmt->i_version  = -1;
    pmt->i_number   = -1;
    pmt->i_pid_pcr  = 0x1FFF;
    pmt->b_selected = false;
    pmt->iod        = NULL;
    pmt->od.i_version = -1;
    ARRAY_INIT( pmt->od.objects );

    pmt->i_last_dts = TS_TICK_UNKNOWN;
    pmt->i_last_dts_byte = 0;

    pmt->p_atsc_si_basepid      = NULL;
    pmt->p_si_sdt_pid = NULL;

    pmt->pcr.i_current = TS_TICK_UNKNOWN;
    pmt->pcr.i_first  = TS_TICK_UNKNOWN;
    pmt->pcr.b_disable = false;
    pmt->pcr.i_first_dts = TS_TICK_UNKNOWN;
    pmt->pcr.i_pcroffset = -1;

    pmt->pcr.b_fix_done = false;

    pmt->eit.i_event_length = 0;
    pmt->eit.i_event_start = 0;

    pmt->arib.i_download_id = -1;
    pmt->arib.i_logo_id = -1;

    return pmt;
}