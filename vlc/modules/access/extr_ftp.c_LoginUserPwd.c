#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ftp_RecvCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ftp_SendCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LoginUserPwd( vlc_object_t *p_access, access_sys_t *p_sys,
                         const char *psz_user, const char *psz_pwd,
                         bool *p_logged )
{
    int i_answer;

    /* Send credentials over channel */
    if( ftp_SendCommand( p_access, p_sys, "USER %s", psz_user ) < 0 ||
        ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0 )
        return -1;

    switch( i_answer / 100 )
    {
        case 2:
            /* X.509 auth successful after AUTH TLS / RFC 2228 sec. 4 */
            if ( i_answer == 232 )
                msg_Dbg( p_access, "user accepted and authenticated" );
            else
                msg_Dbg( p_access, "user accepted" );
            break;
        case 3:
            msg_Dbg( p_access, "password needed" );

            if( ftp_SendCommand( p_access, p_sys, "PASS %s", psz_pwd ) < 0 ||
                ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0 )
                return -1;

            switch( i_answer / 100 )
            {
                case 2:
                    msg_Dbg( p_access, "password accepted" );
                    break;
                case 3:
                {
                    char *psz;
                    msg_Dbg( p_access, "account needed" );
                    psz = var_InheritString( p_access, "ftp-account" );
                    if( ftp_SendCommand( p_access, p_sys, "ACCT %s",
                                         psz ) < 0 ||
                        ftp_RecvCommand( p_access, p_sys, &i_answer, NULL ) < 0 )
                    {
                        free( psz );
                        return -1;
                    }
                    free( psz );

                    if( i_answer / 100 != 2 )
                    {
                        msg_Err( p_access, "account rejected" );
                        vlc_dialog_display_error( p_access,
                          _("Network interaction failed"),
                          "%s", _("Your account was rejected.") );
                        return -1;
                    }
                    msg_Dbg( p_access, "account accepted" );
                    break;
                }

                default:
                    msg_Warn( p_access, "password rejected" );
                    *p_logged = false;
                    return 0;
            }
            break;
        default:
            msg_Warn( p_access, "user rejected" );
            *p_logged = false;
            return 0;
    }

    *p_logged = true;
    return 0;
}