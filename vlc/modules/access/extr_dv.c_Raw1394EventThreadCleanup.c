#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* p_access; } ;
typedef  TYPE_1__ event_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_node; } ;
typedef  TYPE_2__ access_sys_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVCStop (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Raw1394EventThreadCleanup( void *obj )
{
    event_thread_t *p_ev = (event_thread_t *)obj;
    access_sys_t *sys = p_ev->p_access->p_sys;

    AVCStop( p_ev->p_access, sys->i_node );
}