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
struct TYPE_4__ {struct TYPE_4__* p_next; int /*<<< orphan*/  p_dvbpsi; } ;
typedef  TYPE_1__ ts_sections_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_dvbpsi_DetachRawDecoder (int /*<<< orphan*/ ) ; 

void ts_sections_processor_ChainDelete( ts_sections_processor_t *p_chain )
{
    while( p_chain )
    {
        ts_dvbpsi_DetachRawDecoder( p_chain->p_dvbpsi );
        dvbpsi_delete( p_chain->p_dvbpsi );
        ts_sections_processor_t *p_next = p_chain->p_next;
        free( p_chain );
        p_chain = p_next;
    }
}