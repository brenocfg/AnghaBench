#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* p_next; TYPE_1__* p_dvbpsi; } ;
typedef  TYPE_2__ ts_sections_processor_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_decoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_decoder_reset (int /*<<< orphan*/ ,int) ; 

void ts_sections_processor_Reset( ts_sections_processor_t *p_chain )
{
    while( p_chain )
    {
        dvbpsi_decoder_reset( p_chain->p_dvbpsi->p_decoder, true );
        p_chain = p_chain->p_next;
    }
}