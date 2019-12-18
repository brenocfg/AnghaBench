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
struct TYPE_4__ {int /*<<< orphan*/  p_nit; int /*<<< orphan*/  p_sdt; int /*<<< orphan*/  p_pat; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ b_use_nit; TYPE_1__ local; } ;
typedef  TYPE_2__ scan_session_t ;

/* Variables and functions */
 scalar_t__ SCAN_DVB_T ; 

__attribute__((used)) static unsigned scan_session_GetTablesTimeout( const scan_session_t *p_session )
{
    unsigned i_time = 0;
    if( !p_session->local.p_pat )
    {
        i_time = 500;
    }
    else if( !p_session->local.p_sdt )
    {
        i_time = 2*1000;
    }
    else if( !p_session->local.p_nit && p_session->b_use_nit )
    {
        if( p_session->type == SCAN_DVB_T )
            i_time = 6000;
        else
            i_time = 5000;
    }

    return i_time * 2 * 1000;
}