#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* p_stream; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ u; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_pid; } ;
typedef  TYPE_3__ ts_pid_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SCRAMBLED ; 
 int /*<<< orphan*/  SCRAMBLED (TYPE_3__) ; 
 scalar_t__ TYPE_STREAM ; 
 int /*<<< orphan*/  UpdateESScrambledState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void UpdatePIDScrambledState( demux_t *p_demux, ts_pid_t *p_pid, bool b_scrambled )
{
    if( !SCRAMBLED(*p_pid) == !b_scrambled )
        return;

    msg_Warn( p_demux, "scrambled state changed on pid %d (%d->%d)",
              p_pid->i_pid, !!SCRAMBLED(*p_pid), b_scrambled );

    if( b_scrambled )
        p_pid->i_flags |= FLAG_SCRAMBLED;
    else
        p_pid->i_flags &= ~FLAG_SCRAMBLED;

    if( p_pid->type == TYPE_STREAM )
        UpdateESScrambledState( p_demux->out, p_pid->u.p_stream->p_es, b_scrambled );
}