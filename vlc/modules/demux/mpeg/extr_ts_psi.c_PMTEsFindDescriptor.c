#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_first_descriptor; } ;
typedef  TYPE_1__ dvbpsi_pmt_es_t ;
struct TYPE_6__ {int i_tag; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ dvbpsi_descriptor_t ;

/* Variables and functions */

__attribute__((used)) static dvbpsi_descriptor_t *PMTEsFindDescriptor( const dvbpsi_pmt_es_t *p_es,
                                                 int i_tag )
{
    dvbpsi_descriptor_t *p_dr = p_es->p_first_descriptor;;
    while( p_dr && ( p_dr->i_tag != i_tag ) )
        p_dr = p_dr->p_next;
    return p_dr;
}