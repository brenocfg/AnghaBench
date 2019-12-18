#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p_es; int /*<<< orphan*/ * p_block; } ;
struct TYPE_7__ {TYPE_3__ send; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  TYPE_4__ ts_cmd_t ;
typedef  int /*<<< orphan*/  es_out_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_6__ {scalar_t__ p_es; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int es_out_Send (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int CmdExecuteSend( es_out_t *p_out, ts_cmd_t *p_cmd )
{
    block_t *p_block = p_cmd->u.send.p_block;

    p_cmd->u.send.p_block = NULL;

    if( p_block )
    {
        if( p_cmd->u.send.p_es->p_es )
            return es_out_Send( p_out, p_cmd->u.send.p_es->p_es, p_block );
        block_Release( p_block );
    }
    return VLC_EGENERIC;
}