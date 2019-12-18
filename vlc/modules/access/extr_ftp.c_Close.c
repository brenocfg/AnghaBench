#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_creds; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  clearCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  ftp_RecvCommand (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ftp_SendCommand (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ftp_StopStream (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_ClientDelete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close( vlc_object_t *p_access, access_sys_t *p_sys )
{
    msg_Dbg( p_access, "stopping stream" );
    ftp_StopStream( p_access, p_sys );

    if( ftp_SendCommand( p_access, p_sys, "QUIT" ) < 0 )
    {
        msg_Warn( p_access, "cannot quit" );
    }
    else
    {
        ftp_RecvCommand( p_access, p_sys, NULL, NULL );
    }

    clearCmd( p_sys );

    /* free memory */
    vlc_UrlClean( &p_sys->url );
    vlc_tls_ClientDelete( p_sys->p_creds );
}