#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cdtpid; scalar_t__ tdtpid; scalar_t__ eitpid; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ts_si_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIDRelease (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dvbpsi_DetachDemux (int /*<<< orphan*/ ) ; 
 scalar_t__ dvbpsi_decoder_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbpsi_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void ts_si_Del( demux_t *p_demux, ts_si_t *si )
{
    if( dvbpsi_decoder_present( si->handle ) )
        dvbpsi_DetachDemux( si->handle );
    dvbpsi_delete( si->handle );
    if( si->eitpid )
        PIDRelease( p_demux, si->eitpid );
    if( si->tdtpid )
        PIDRelease( p_demux, si->tdtpid );
    if( si->cdtpid )
        PIDRelease( p_demux, si->cdtpid );
    free( si );
}