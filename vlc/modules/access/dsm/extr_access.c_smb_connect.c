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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_session; int /*<<< orphan*/  i_fd; int /*<<< orphan*/  psz_path; int /*<<< orphan*/  i_tid; int /*<<< orphan*/  psz_share; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int DSM_ERROR_NT ; 
 int DSM_SUCCESS ; 
 int EACCES ; 
 int ENOENT ; 
 scalar_t__ NT_STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  SMB_MOD_RO ; 
 int smb_fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ smb_session_get_nt_status (int /*<<< orphan*/ ) ; 
 int smb_session_login (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_session_set_creds (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int smb_tree_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smb_connect( stream_t *p_access, const char *psz_login,
                        const char *psz_password, const char *psz_domain)
{
    access_sys_t *p_sys = p_access->p_sys;
    int ret;

    smb_session_set_creds( p_sys->p_session, psz_domain,
                           psz_login, psz_password );
    if( smb_session_login( p_sys->p_session ) != DSM_SUCCESS )
        return EACCES;

    if( !p_sys->psz_share )
        return 0;

    /* Connect to the share */
    ret = smb_tree_connect( p_sys->p_session, p_sys->psz_share, &p_sys->i_tid );
    if( ret != DSM_SUCCESS )
        goto error;

    /* Let's finally ask a handle to the file we wanna read ! */
    ret = smb_fopen( p_sys->p_session, p_sys->i_tid, p_sys->psz_path,
                     SMB_MOD_RO, &p_sys->i_fd );
    if( ret != DSM_SUCCESS )
        goto error;

    return 0;

error:
    return ret == DSM_ERROR_NT && smb_session_get_nt_status( p_sys->p_session )
        == NT_STATUS_ACCESS_DENIED ? EACCES : ENOENT;
}