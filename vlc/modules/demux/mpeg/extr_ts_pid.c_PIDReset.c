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
struct TYPE_3__ {scalar_t__ i_refcount; int i_cc; int /*<<< orphan*/  prevpktbytes; int /*<<< orphan*/  type; int /*<<< orphan*/  i_flags; scalar_t__ i_dup; } ;
typedef  TYPE_1__ ts_pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SCRAMBLED ; 
 int /*<<< orphan*/  PREVPKTKEEPBYTES ; 
 int /*<<< orphan*/  TYPE_FREE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PIDReset( ts_pid_t *pid )
{
    assert(pid->i_refcount == 0);
    pid->i_cc       = 0xff;
    pid->i_dup      = 0;
    pid->i_flags    &= ~FLAG_SCRAMBLED;
    pid->type = TYPE_FREE;
    memset(pid->prevpktbytes, 0, PREVPKTKEEPBYTES);
}