#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {char* psz_path; char* psz_host; int /*<<< orphan*/  i_port; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_23__ {char* psz_realm; scalar_t__ i_get_order; } ;
typedef  TYPE_2__ vlc_credential ;
struct smb2_url {int /*<<< orphan*/  server; int /*<<< orphan*/  share; } ;
struct access_sys {int /*<<< orphan*/  error_status; TYPE_1__ encoded_url; int /*<<< orphan*/ * smb2; int /*<<< orphan*/ * share_enum; int /*<<< orphan*/ * smb2dir; int /*<<< orphan*/ * smb2fh; } ;
struct TYPE_24__ {void* pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  psz_url; struct access_sys* p_sys; } ;
typedef  TYPE_3__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  DirRead ; 
 int /*<<< orphan*/  EIO ; 
 void* FileControl ; 
 int /*<<< orphan*/  FileRead ; 
 int /*<<< orphan*/ * FileSeek ; 
 scalar_t__ GET_FROM_DIALOG ; 
 int /*<<< orphan*/  SMB2_NEGOTIATE_SIGNING_ENABLED ; 
 int /*<<< orphan*/  SMB_LOGIN_DIALOG_TEXT ; 
 int /*<<< orphan*/  SMB_LOGIN_DIALOG_TITLE ; 
 int /*<<< orphan*/  ShareEnum ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_ETIMEOUT ; 
 scalar_t__ VLC_SMB2_STATUS_DENIED (int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_VOID ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  smb2_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb2_destroy_url (struct smb2_url*) ; 
 char* smb2_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smb2_init_context () ; 
 struct smb2_url* smb2_parse_url (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  smb2_set_security_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Create (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 char* var_InheritString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 scalar_t__ vlc_UrlParseFixup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_2__*) ; 
 scalar_t__ vlc_credential_get (TYPE_2__*,TYPE_3__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_3__*,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ vlc_killed () ; 
 struct access_sys* vlc_obj_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vlc_smb2_disconnect_share (TYPE_3__*) ; 
 int vlc_smb2_open_share (TYPE_3__*,struct smb2_url*,TYPE_2__*) ; 
 char* vlc_smb2_resolve (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 char* vlc_uri_compose (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_uri_decode (char*) ; 

__attribute__((used)) static int
Open(vlc_object_t *p_obj)
{
    stream_t *access = (stream_t *)p_obj;
    struct access_sys *sys = vlc_obj_calloc(p_obj, 1, sizeof (*sys));
    struct smb2_url *smb2_url = NULL;
    char *var_domain = NULL;

    if (unlikely(sys == NULL))
        return VLC_ENOMEM;
    access->p_sys = sys;

    /* Parse the encoded URL */
    if (vlc_UrlParseFixup(&sys->encoded_url, access->psz_url) != 0)
        return VLC_ENOMEM;

    sys->smb2 = smb2_init_context();
    if (sys->smb2 == NULL)
    {
        msg_Err(access, "smb2_init_context failed");
        goto error;
    }

    smb2_set_security_mode(sys->smb2, SMB2_NEGOTIATE_SIGNING_ENABLED);

    if (sys->encoded_url.psz_path == NULL)
        sys->encoded_url.psz_path = (char *) "/";

    char *resolved_host = vlc_smb2_resolve(access, sys->encoded_url.psz_host,
                                           sys->encoded_url.i_port);

    /* smb2_* functions need a decoded url. Re compose the url from the
     * modified sys->encoded_url (with the resolved host). */
    char *url;
    if (resolved_host != NULL)
    {
        vlc_url_t resolved_url = sys->encoded_url;
        resolved_url.psz_host = resolved_host;
        url = vlc_uri_compose(&resolved_url);
        free(resolved_host);
    }
    else
        url = vlc_uri_compose(&sys->encoded_url);
    if (!vlc_uri_decode(url))
    {
        free(url);
        goto error;
    }
    smb2_url = smb2_parse_url(sys->smb2, url);
    free(url);

    if (!smb2_url || !smb2_url->share || !smb2_url->server)
    {
        msg_Err(access, "smb2_parse_url failed");
        goto error;
    }

    int ret = -1;
    vlc_credential credential;
    vlc_credential_init(&credential, &sys->encoded_url);
    var_domain = var_InheritString(access, "smb-domain");
    credential.psz_realm = var_domain;

    /* First, try Guest login or using "smb-" options (without
     * keystore/user interaction) */
    vlc_credential_get(&credential, access, "smb-user", "smb-pwd", NULL,
                       NULL);
    ret = vlc_smb2_open_share(access, smb2_url, &credential);

    while (ret == -1
        && (!sys->error_status || VLC_SMB2_STATUS_DENIED(sys->error_status))
        && vlc_credential_get(&credential, access, "smb-user", "smb-pwd",
                              SMB_LOGIN_DIALOG_TITLE, SMB_LOGIN_DIALOG_TEXT,
                              smb2_url->server))
    {
        sys->error_status = 0;
        ret = vlc_smb2_open_share(access, smb2_url, &credential);
    }
    if (ret == 0)
        vlc_credential_store(&credential, access);
    vlc_credential_clean(&credential);

    if (ret != 0)
    {
        const char *error = smb2_get_error(sys->smb2);
        if (error && *error)
            vlc_dialog_display_error(access,
                                     _("SMB2 operation failed"), "%s", error);
        if (credential.i_get_order == GET_FROM_DIALOG)
        {
            /* Tell other smb modules (likely dsm) that we already requested
             * credential to the users and that it it useless to try again.
             * This avoid to show 2 login dialogs for the same access. */
            var_Create(access, "smb-dialog-failed", VLC_VAR_VOID);
        }
        goto error;
    }

    if (sys->smb2fh != NULL)
    {
        access->pf_read = FileRead;
        access->pf_seek = FileSeek;
        access->pf_control = FileControl;
    }
    else if (sys->smb2dir != NULL)
    {
        access->pf_readdir = DirRead;
        access->pf_seek = NULL;
        access->pf_control = access_vaDirectoryControlHelper;
    }
    else if (sys->share_enum != NULL)
    {
        access->pf_readdir = ShareEnum;
        access->pf_seek = NULL;
        access->pf_control = access_vaDirectoryControlHelper;
    }
    else
        vlc_assert_unreachable();

    smb2_destroy_url(smb2_url);
    free(var_domain);
    return VLC_SUCCESS;

error:
    if (smb2_url != NULL)
        smb2_destroy_url(smb2_url);
    if (sys->smb2 != NULL)
    {
        vlc_smb2_disconnect_share(access);
        smb2_destroy_context(sys->smb2);
    }
    vlc_UrlClean(&sys->encoded_url);
    free(var_domain);

    /* Returning VLC_ETIMEOUT will stop the module probe and prevent to load
     * the next smb module. The smb2 module can return this specific error in
     * case of network error (EIO) or when the user asked to cancel it
     * (vlc_killed()). Indeed, in these cases, it is useless to try next smb
     * modules. */
    return vlc_killed() || sys->error_status == -EIO ? VLC_ETIMEOUT
         : VLC_EGENERIC;
}