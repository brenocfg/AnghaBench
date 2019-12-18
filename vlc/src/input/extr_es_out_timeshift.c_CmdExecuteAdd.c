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
struct TYPE_7__ {int /*<<< orphan*/  p_fmt; TYPE_1__* p_es; } ;
struct TYPE_8__ {TYPE_2__ add; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
typedef  TYPE_4__ ts_cmd_t ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CmdExecuteAdd( es_out_t *p_out, ts_cmd_t *p_cmd )
{
    p_cmd->u.add.p_es->p_es = es_out_Add( p_out, p_cmd->u.add.p_fmt );
}