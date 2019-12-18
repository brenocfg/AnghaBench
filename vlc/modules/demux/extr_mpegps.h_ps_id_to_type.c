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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {size_t i_es; TYPE_1__* es; } ;
typedef  TYPE_2__ ps_psm_t ;
struct TYPE_4__ {scalar_t__ i_id; int /*<<< orphan*/  i_type; } ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t ps_id_to_type( const ps_psm_t *p_psm, uint16_t i_id )
{
    size_t i;
    for( i = 0; p_psm && i < p_psm->i_es; i++ )
    {
        if( p_psm->es[i].i_id == i_id ) return p_psm->es[i].i_type;
    }
    return 0;
}