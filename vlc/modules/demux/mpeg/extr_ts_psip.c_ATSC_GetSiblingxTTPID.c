#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {TYPE_1__* p_ctx; } ;
typedef  TYPE_2__ ts_psip_t ;
typedef  int /*<<< orphan*/  ts_pid_t ;
typedef  int /*<<< orphan*/  ts_pid_list_t ;
struct TYPE_9__ {scalar_t__ i_table_type; int /*<<< orphan*/  i_table_type_pid; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ dvbpsi_atsc_mgt_table_t ;
struct TYPE_10__ {TYPE_3__* p_first_table; } ;
typedef  TYPE_4__ dvbpsi_atsc_mgt_t ;
struct TYPE_7__ {scalar_t__ i_tabletype; } ;

/* Variables and functions */
 scalar_t__ ATSC_TABLE_TYPE_EIT_0 ; 
 scalar_t__ ATSC_TABLE_TYPE_ETT_0 ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/ * ts_pid_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ts_pid_t *ATSC_GetSiblingxTTPID( ts_pid_list_t *p_list, const dvbpsi_atsc_mgt_t *p_mgt, ts_psip_t *p_psip )
{
    uint16_t i_lookup;
    assert( p_psip->p_ctx->i_tabletype );
    if( p_psip->p_ctx->i_tabletype >= ATSC_TABLE_TYPE_ETT_0 )
        i_lookup = p_psip->p_ctx->i_tabletype - ATSC_TABLE_TYPE_ETT_0 + ATSC_TABLE_TYPE_EIT_0;
    else
        i_lookup = p_psip->p_ctx->i_tabletype - ATSC_TABLE_TYPE_EIT_0 + ATSC_TABLE_TYPE_ETT_0;

    for( const dvbpsi_atsc_mgt_table_t *p_tab = p_mgt->p_first_table;
                                        p_tab; p_tab = p_tab->p_next )
    {
        if( p_tab->i_table_type == i_lookup )
            return ts_pid_Get( p_list, p_tab->i_table_type_pid );
    }
    return NULL;
}