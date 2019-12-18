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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__* pi_system_ids; } ;
typedef  TYPE_1__ system_ids_t ;

/* Variables and functions */

__attribute__((used)) static bool CheckSystemID( const system_ids_t *p_ids, uint16_t i_id )
{
    int i = 0;
    if( !p_ids ) return true;      /* dummy session for high-level CI intf */

    while ( p_ids->pi_system_ids[i] )
    {
        if ( p_ids->pi_system_ids[i] == i_id )
            return true;
        i++;
    }

    return false;
}