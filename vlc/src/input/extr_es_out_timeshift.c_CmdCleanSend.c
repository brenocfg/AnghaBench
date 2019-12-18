#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ p_block; } ;
struct TYPE_6__ {TYPE_1__ send; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ ts_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (scalar_t__) ; 

__attribute__((used)) static void CmdCleanSend( ts_cmd_t *p_cmd )
{
    if( p_cmd->u.send.p_block )
        block_Release( p_cmd->u.send.p_block );
}