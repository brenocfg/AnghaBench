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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Stop( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    msg_Dbg( p_access, "closing stream" );
    if( p_sys->stream != NULL )
    {
        vlc_tls_Close( p_sys->stream );
        p_sys->stream = NULL;
    }
}