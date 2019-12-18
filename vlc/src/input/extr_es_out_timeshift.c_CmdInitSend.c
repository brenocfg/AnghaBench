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
struct TYPE_5__ {int /*<<< orphan*/ * p_block; int /*<<< orphan*/ * p_es; } ;
struct TYPE_6__ {TYPE_1__ send; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  i_date; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_3__ ts_cmd_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_SEND ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void CmdInitSend( ts_cmd_t *p_cmd, es_out_id_t *p_es, block_t *p_block )
{
    p_cmd->i_type = C_SEND;
    p_cmd->i_date = vlc_tick_now();
    p_cmd->u.send.p_es = p_es;
    p_cmd->u.send.p_block = p_block;
}