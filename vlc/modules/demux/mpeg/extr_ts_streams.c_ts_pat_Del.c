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
struct TYPE_5__ {TYPE_4__ programs; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ts_pat_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (TYPE_4__) ; 
 int /*<<< orphan*/  PIDRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dvbpsi_decoder_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_pat_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void ts_pat_Del( demux_t *p_demux, ts_pat_t *pat )
{
    if( dvbpsi_decoder_present( pat->handle ) )
        dvbpsi_pat_detach( pat->handle );
    dvbpsi_delete( pat->handle );
    for( int i=0; i<pat->programs.i_size; i++ )
        PIDRelease( p_demux, pat->programs.p_elems[i] );
    ARRAY_RESET( pat->programs );
    free( pat );
}