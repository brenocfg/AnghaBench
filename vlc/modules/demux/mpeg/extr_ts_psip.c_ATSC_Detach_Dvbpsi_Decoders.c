#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dvbpsi_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_DetachDemux (int /*<<< orphan*/ *) ; 
 scalar_t__ dvbpsi_decoder_present (int /*<<< orphan*/ *) ; 

void ATSC_Detach_Dvbpsi_Decoders( dvbpsi_t *p_handle )
{
    if( dvbpsi_decoder_present( p_handle ) )
        dvbpsi_DetachDemux( p_handle );
}