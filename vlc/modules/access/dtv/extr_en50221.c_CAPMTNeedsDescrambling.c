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
struct TYPE_5__ {size_t i_es_count; TYPE_1__* p_es; scalar_t__ p_program_descriptors; } ;
typedef  TYPE_2__ en50221_capmt_info_t ;
struct TYPE_4__ {scalar_t__ p_descriptors; } ;

/* Variables and functions */

__attribute__((used)) static bool CAPMTNeedsDescrambling( const en50221_capmt_info_t *p_info )
{
    if( p_info->p_program_descriptors )
        return true;

    for( size_t i=0; i<p_info->i_es_count; i++ )
    {
        if( p_info->p_es[i].p_descriptors )
            return true;
    }

    return false;
}