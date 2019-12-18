#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_dvbpsi; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ ts_sections_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_packet_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ts_sections_processor_Push( ts_sections_processor_t *p_chain,
                                 const uint8_t *p_buf )
{
    for( ts_sections_processor_t *p_proc = p_chain;
         p_proc; p_proc = p_proc->p_next )
    {
        dvbpsi_packet_push( p_chain->p_dvbpsi, (uint8_t *) p_buf );
    }
}