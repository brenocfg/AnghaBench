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
struct TYPE_5__ {int /*<<< orphan*/ * p_es; } ;
struct TYPE_6__ {TYPE_1__ del; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  i_date; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_3__ ts_cmd_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_DEL ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static int CmdInitDel( ts_cmd_t *p_cmd, es_out_id_t *p_es )
{
    p_cmd->i_type = C_DEL;
    p_cmd->i_date = vlc_tick_now();
    p_cmd->u.del.p_es = p_es;
    return VLC_SUCCESS;
}