#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* psz_realm; char* psz_username; char* psz_password; } ;
typedef  TYPE_1__ vlc_credential ;
struct TYPE_17__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_18__ {char* netbios_name; int /*<<< orphan*/  p_session; int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  SMB1_LOGIN_DIALOG_TITLE ; 
 int /*<<< orphan*/  SMB_LOGIN_DIALOG_TEXT ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,...) ; 
 int smb_connect (TYPE_2__*,char const*,char const*,char const*) ; 
 int smb_session_is_guest (int /*<<< orphan*/ ) ; 
 char* var_InheritString (TYPE_2__*,char*) ; 
 scalar_t__ var_Type (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_1__*) ; 
 scalar_t__ vlc_credential_get (TYPE_1__*,TYPE_2__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int login( stream_t *p_access )
{
    int i_ret = VLC_EGENERIC;
    access_sys_t *p_sys = p_access->p_sys;
    vlc_credential credential;
    char *psz_var_domain;
    const char *psz_login, *psz_password, *psz_domain;
    bool b_guest = false;

    vlc_credential_init( &credential, &p_sys->url );
    psz_var_domain = var_InheritString( p_access, "smb-domain" );
    credential.psz_realm = psz_var_domain ? psz_var_domain : NULL;

    vlc_credential_get( &credential, p_access, "smb-user", "smb-pwd",
                        NULL, NULL );

    if( !credential.psz_username )
    {
        psz_login = "Guest";
        psz_password = "";
        b_guest = true;
    }
    else
    {
        psz_login = credential.psz_username;
        psz_password = credential.psz_password;
    }
    psz_domain = credential.psz_realm ? credential.psz_realm : p_sys->netbios_name;

    /* Try to authenticate on the remote machine */
    int connect_err = smb_connect( p_access, psz_login, psz_password, psz_domain );
    if( connect_err == ENOENT )
        goto error;

    if( connect_err == EACCES )
    {
        if (var_Type(p_access, "smb-dialog-failed") != 0)
        {
            /* A higher priority smb module (likely smb2) already requested
             * credentials to the users. It is useless to request it again. */
            goto error;
        }
        while( connect_err == EACCES
            && vlc_credential_get( &credential, p_access, "smb-user", "smb-pwd",
                                   SMB1_LOGIN_DIALOG_TITLE,
                                   SMB_LOGIN_DIALOG_TEXT, p_sys->netbios_name ) )
        {
            b_guest = false;
            psz_login = credential.psz_username;
            psz_password = credential.psz_password;
            psz_domain = credential.psz_realm ? credential.psz_realm
                                              : p_sys->netbios_name;
            connect_err = smb_connect( p_access, psz_login, psz_password, psz_domain );
        }

        if( connect_err != 0 )
        {
            msg_Err( p_access, "Unable to login" );
            goto error;
        }
    }
    assert( connect_err == 0 );

    if( smb_session_is_guest( p_sys->p_session ) == 1 )
    {
        msg_Warn( p_access, "Login failure but you were logged in as a Guest");
        b_guest = true;
    }

    msg_Warn( p_access, "Creds: username = '%s', domain = '%s'",
             psz_login, psz_domain );
    if( !b_guest )
        vlc_credential_store( &credential, p_access );

    i_ret = VLC_SUCCESS;
error:
    vlc_credential_clean( &credential );
    free( psz_var_domain );
    return i_ret;
}