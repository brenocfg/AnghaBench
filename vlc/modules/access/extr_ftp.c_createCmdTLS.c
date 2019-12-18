#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  psz_host; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cmd; TYPE_1__ url; int /*<<< orphan*/  p_creds; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlc_tls_ClientSessionCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int createCmdTLS( vlc_object_t *p_access, access_sys_t *p_sys,
                         const char *psz_session_name )
{
    /* TLS/SSL handshake */
    vlc_tls_t *secure = vlc_tls_ClientSessionCreate( p_sys->p_creds,
                                                     p_sys->cmd,
                                                     p_sys->url.psz_host,
                                                     psz_session_name,
                                                     NULL, NULL );
    if( secure == NULL )
    {
        msg_Err( p_access, "cannot establish FTP/TLS session on command channel" );
        return -1;
    }
    p_sys->cmd = secure;
    return 0;
}