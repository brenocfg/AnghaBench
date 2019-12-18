#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {size_t i_nit; TYPE_3__** pp_nit; } ;
struct TYPE_7__ {TYPE_1__ others; } ;
typedef  TYPE_2__ scan_session_t ;
struct TYPE_8__ {scalar_t__ i_network_id; } ;
typedef  TYPE_3__ dvbpsi_nit_t ;

/* Variables and functions */

__attribute__((used)) static bool GetOtherNetworkNIT( scan_session_t *p_session, uint16_t i_network_id,
                                dvbpsi_nit_t ***ppp_nit )
{
    for( size_t i=0; i<p_session->others.i_nit; i++ )
    {
        if( p_session->others.pp_nit[i]->i_network_id == i_network_id )
        {
            *ppp_nit = &p_session->others.pp_nit[i];
            return true;
        }
    }

    return false;
}