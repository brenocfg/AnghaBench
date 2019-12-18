#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {scalar_t__ psz_path; } ;
struct TYPE_9__ {scalar_t__ b_unicode; } ;
struct TYPE_11__ {TYPE_2__ url; TYPE_1__ features; int /*<<< orphan*/  sz_epsv_ip; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * IsASCII (scalar_t__) ; 
 int /*<<< orphan*/ * IsUTF8 (scalar_t__) ; 
 scalar_t__ Login (int /*<<< orphan*/ *,TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  clearCmd (TYPE_3__*) ; 
 int ftp_RecvCommand (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ftp_SendCommand (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ net_GetPeerAddress (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (scalar_t__) ; 
 int vlc_tls_GetFD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Connect( vlc_object_t *p_access, access_sys_t *p_sys, const char *path )
{
    if( Login( p_access, p_sys, path ) < 0 )
        return -1;

    /* Extended passive mode */
    if( ftp_SendCommand( p_access, p_sys, "EPSV ALL" ) < 0 )
    {
        msg_Err( p_access, "cannot request extended passive mode" );
        goto error;
    }

    if( ftp_RecvCommand( p_access, p_sys, NULL, NULL ) == 2 )
    {
        int fd = vlc_tls_GetFD(p_sys->cmd);
        if( net_GetPeerAddress( fd, p_sys->sz_epsv_ip, NULL ) )
            goto error;
    }
    else
    {
        /* If ESPV ALL fails, we fallback to PASV.
         * We have to restart the connection in case there is a NAT that
         * understands EPSV ALL in the way, and hence won't allow PASV on
         * the initial connection.
         */
        msg_Info( p_access, "FTP Extended passive mode disabled" );
        clearCmd( p_sys );

        if( Login( p_access, p_sys, path ) )
            goto error;
    }

    if( p_sys->url.psz_path &&
        (p_sys->features.b_unicode ? IsUTF8 : IsASCII)(p_sys->url.psz_path) == NULL )
    {
        msg_Err( p_access, "unsupported path: \"%s\"", p_sys->url.psz_path );
        goto error;
    }

    /* check binary mode support */
    if( ftp_SendCommand( p_access, p_sys, "TYPE I" ) < 0 ||
        ftp_RecvCommand( p_access, p_sys, NULL, NULL ) != 2 )
    {
        msg_Err( p_access, "cannot set binary transfer mode" );
        goto error;
    }

    return 0;

error:
    clearCmd( p_sys );
    return -1;
}