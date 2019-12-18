#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_size; int /*<<< orphan*/ * p_elems; } ;
struct TYPE_5__ {TYPE_4__ eit; scalar_t__ handle; int /*<<< orphan*/  p_eas_es; scalar_t__ p_ctx; } ;
typedef  TYPE_1__ ts_psip_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (TYPE_4__) ; 
 int /*<<< orphan*/  ATSC_Detach_Dvbpsi_Decoders (scalar_t__) ; 
 int /*<<< orphan*/  PIDRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_delete (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_pes_ChainDelete_es (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_psip_context_Delete (scalar_t__) ; 

void ts_psip_Del( demux_t *p_demux, ts_psip_t *psip )
{
    if( psip->p_ctx )
        ts_psip_context_Delete( psip->p_ctx );

    ts_pes_ChainDelete_es( p_demux, psip->p_eas_es );

    if( psip->handle )
    {
        ATSC_Detach_Dvbpsi_Decoders( psip->handle );
        dvbpsi_delete( psip->handle );
    }

    for( int i=0; i<psip->eit.i_size; i++ )
        PIDRelease( p_demux, psip->eit.p_elems[i] );
    ARRAY_RESET( psip->eit );

    free( psip );
}