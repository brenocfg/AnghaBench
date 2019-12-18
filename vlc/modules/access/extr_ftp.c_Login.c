#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  psz_host; } ;
typedef  TYPE_2__ vlc_url_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_23__ {char* psz_username; int /*<<< orphan*/  psz_password; } ;
typedef  TYPE_3__ vlc_credential ;
struct TYPE_20__ {int /*<<< orphan*/  b_authtls; } ;
struct TYPE_21__ {int /*<<< orphan*/  i_port; int /*<<< orphan*/  psz_host; } ;
struct TYPE_24__ {scalar_t__ tlsmode; TYPE_15__ features; int /*<<< orphan*/ * cmd; TYPE_1__ url; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 scalar_t__ EXPLICIT ; 
 int /*<<< orphan*/  FeaturesCheck ; 
 scalar_t__ IMPLICIT ; 
 int /*<<< orphan*/  LOGIN_DIALOG_TEXT ; 
 int /*<<< orphan*/  LOGIN_DIALOG_TITLE ; 
 scalar_t__ LoginUserPwd (int /*<<< orphan*/ *,TYPE_4__*,char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ NONE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  clearCmd (TYPE_4__*) ; 
 scalar_t__ createCmdTLS (int /*<<< orphan*/ *,TYPE_4__*,char*) ; 
 scalar_t__ ftp_RecvAnswer (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_15__*) ; 
 int ftp_RecvCommand (int /*<<< orphan*/ *,TYPE_4__*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ftp_SendCommand (int /*<<< orphan*/ *,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_2__*) ; 
 scalar_t__ vlc_UrlParseFixup (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_3__*) ; 
 scalar_t__ vlc_credential_get (TYPE_3__*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenTCP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Login( vlc_object_t *p_access, access_sys_t *p_sys, const char *path )
{
    int i_answer;

    /* *** Open a TCP connection with server *** */
    p_sys->cmd = vlc_tls_SocketOpenTCP( p_access, p_sys->url.psz_host,
                                        p_sys->url.i_port );
    if( p_sys->cmd == NULL )
    {
        msg_Err( p_access, "connection failed" );
        vlc_dialog_display_error( p_access, _("Network interaction failed"), "%s",
            _("VLC could not connect with the given server.") );
        goto error;
    }

    if ( p_sys->tlsmode == IMPLICIT ) /* FTPS Mode */
    {
        if ( createCmdTLS( p_access, p_sys, "ftps") < 0 )
            goto error;
    }

    while( ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) == 1 );

    if( i_answer / 100 != 2 )
    {
        msg_Err( p_access, "connection rejected" );
        vlc_dialog_display_error( p_access, _("Network interaction failed"), "%s",
            _("VLC's connection to the given server was rejected.") );
        goto error;
    }

    msg_Dbg( p_access, "connection accepted (%d)", i_answer );

    /* Features check first */
    if( ftp_SendCommand( p_access, p_sys, "FEAT" ) < 0
     || ftp_RecvAnswer( p_access, p_sys, NULL, NULL,
                        FeaturesCheck, &p_sys->features ) < 0 )
    {
         msg_Err( p_access, "cannot get server features" );
         goto error;
    }

    /* Create TLS Session */
    if( p_sys->tlsmode == EXPLICIT )
    {
        if ( ! p_sys->features.b_authtls )
        {
            msg_Err( p_access, "Server does not support TLS" );
            goto error;
        }

        if( ftp_SendCommand( p_access, p_sys, "AUTH TLS" ) < 0
         || ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0
         || i_answer != 234 )
        {
             msg_Err( p_access, "cannot switch to TLS: server replied with code %d",
                      i_answer );
             goto error;
        }

        if( createCmdTLS( p_access, p_sys, "ftpes") < 0 )
        {
            goto error;
        }
    }

    if( p_sys->tlsmode != NONE )
    {
        if( ftp_SendCommand( p_access, p_sys, "PBSZ 0" ) < 0 ||
            ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0 ||
            i_answer != 200 )
        {
            msg_Err( p_access, "Can't truncate Protection buffer size for TLS" );
            goto error;
        }

        if( ftp_SendCommand( p_access, p_sys, "PROT P" ) < 0 ||
            ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0 ||
            i_answer != 200 )
        {
            msg_Err( p_access, "Can't set Data channel protection" );
            goto error;
        }
    }

    vlc_url_t url;
    vlc_credential credential;
    if( vlc_UrlParseFixup( &url, path ) != 0 )
    {
        vlc_UrlClean( &url );
        goto error;
    }
    vlc_credential_init( &credential, &url );
    bool b_logged = false;

    /* First: try credentials from url / option */
    vlc_credential_get( &credential, p_access, "ftp-user", "ftp-pwd",
                        NULL, NULL );
    do
    {
        const char *psz_username = credential.psz_username;

        if( psz_username == NULL ) /* use anonymous by default */
            psz_username = "anonymous";

        if( LoginUserPwd( p_access, p_sys, psz_username,
                          credential.psz_password, &b_logged ) != 0
         || b_logged )
            break;
    }
    while( vlc_credential_get( &credential, p_access, "ftp-user", "ftp-pwd",
                               LOGIN_DIALOG_TITLE, LOGIN_DIALOG_TEXT,
                               url.psz_host ) );

    if( b_logged )
    {
        vlc_credential_store( &credential, p_access );
        vlc_credential_clean( &credential );
        vlc_UrlClean( &url );
        return 0;
    }
    vlc_credential_clean( &credential );
    vlc_UrlClean( &url );
error:
    clearCmd( p_sys );
    return -1;
}