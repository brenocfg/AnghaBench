#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_position; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ Describe (TYPE_1__*,char**) ; 
 scalar_t__ Start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Stop (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static int Restart( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;
    char *psz_location = NULL;

    msg_Dbg( p_access, "Restart the stream" );
    p_sys->i_start = p_sys->i_position;

    /* */
    msg_Dbg( p_access, "stopping the stream" );
    Stop( p_access );

    /* */
    msg_Dbg( p_access, "describe the stream" );
    if( Describe( p_access, &psz_location ) )
    {
        msg_Err( p_access, "describe failed" );
        return VLC_EGENERIC;
    }
    free( psz_location );

    /* */
    if( Start( p_access, 0 ) )
    {
        msg_Err( p_access, "Start failed" );
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}