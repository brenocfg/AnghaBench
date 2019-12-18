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
typedef  int /*<<< orphan*/  ts_pmt_t ;
struct TYPE_3__ {struct TYPE_3__* p_extraes; int /*<<< orphan*/  const* p_program; int /*<<< orphan*/  id; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ ts_es_t ;

/* Variables and functions */

size_t ts_Count_es( const ts_es_t *p_es, bool b_active, const ts_pmt_t *p_pmt )
{
    size_t i=0;
    for( ; p_es; p_es = p_es->p_next )
    {
        i += ( b_active ) ? !!p_es->id : ( ( !p_pmt || p_pmt == p_es->p_program ) ? 1 : 0 );
        i += ts_Count_es( p_es->p_extraes, b_active, p_pmt );
    }
    return i;
}