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
struct TYPE_4__ {int /*<<< orphan*/ * p_decoder; } ;
typedef  TYPE_1__ dvbpsi_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_decoder_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ dvbpsi_decoder_present (TYPE_1__*) ; 

void ts_dvbpsi_DetachRawDecoder( dvbpsi_t *p_dvbpsi )
{
    if( dvbpsi_decoder_present( p_dvbpsi ) )
        dvbpsi_decoder_delete( p_dvbpsi->p_decoder );
    p_dvbpsi->p_decoder = NULL;
}