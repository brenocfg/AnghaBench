#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_6__ {scalar_t__ p_shout; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  shout_close (scalar_t__) ; 
 int /*<<< orphan*/  shout_free (scalar_t__) ; 
 int /*<<< orphan*/  shout_shutdown () ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_access_out_t *p_access = (sout_access_out_t*)p_this;
    sout_access_out_sys_t *p_sys = p_access->p_sys;

    if( p_sys->p_shout )
    {
        shout_close( p_sys->p_shout );
        shout_free( p_sys->p_shout );
        shout_shutdown();
    }
    free( p_sys );
    msg_Dbg( p_access, "shout access output closed" );
}