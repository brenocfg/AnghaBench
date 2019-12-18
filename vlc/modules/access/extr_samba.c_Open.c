#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  psz_host; int /*<<< orphan*/ * psz_path; } ;
typedef  TYPE_1__ vlc_url_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_17__ {char* psz_realm; int /*<<< orphan*/  psz_password; int /*<<< orphan*/  psz_username; } ;
typedef  TYPE_2__ vlc_credential ;
typedef  scalar_t__ uint64_t ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_18__ {int /*<<< orphan*/  psz_location; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_readdir; TYPE_4__* p_sys; int /*<<< orphan*/  psz_url; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_19__ {int i_smb; scalar_t__ size; TYPE_1__ url; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  DirRead ; 
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  SMB_LOGIN_DIALOG_TEXT ; 
 int /*<<< orphan*/  SMB_LOGIN_DIALOG_TITLE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Seek ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_auth ; 
 char* smb_get_uri (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ smbc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smbc_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smbc_opendir (char*) ; 
 scalar_t__ smbc_stat (char*,struct stat*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* var_InheritString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 scalar_t__ vlc_UrlParseFixup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_credential_get (TYPE_2__*,TYPE_3__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_2__*,TYPE_3__*) ; 
 TYPE_4__* vlc_obj_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 
 char* vlc_uri_decode_duplicate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    stream_t *access = (stream_t *)obj;
    vlc_url_t url;
    vlc_credential credential;
    char *psz_decoded_path = NULL, *uri, *psz_var_domain = NULL;
    int fd;
    uint64_t size;
    bool is_dir;

    if (smbc_init(smb_auth, 0))
        return VLC_EGENERIC;

    if (vlc_UrlParseFixup(&url, access->psz_url) != 0)
    {
        vlc_UrlClean(&url);
        return VLC_EGENERIC;
    }

    if (url.psz_path != NULL)
    {
        psz_decoded_path = vlc_uri_decode_duplicate(url.psz_path);
        if (psz_decoded_path == NULL)
        {
            vlc_UrlClean(&url);
            return VLC_EGENERIC;
        }
    }

    vlc_credential_init(&credential, &url);
    psz_var_domain = var_InheritString(access, "smb-domain");
    credential.psz_realm = psz_var_domain;
    vlc_credential_get(&credential, access, "smb-user", "smb-pwd", NULL, NULL);

    for (;;)
    {
        struct stat st;

        uri = smb_get_uri(credential.psz_realm, credential.psz_username,
                          credential.psz_password, url.psz_host,
                          psz_decoded_path, NULL);
        if (uri == NULL)
        {
            vlc_credential_clean(&credential);
            free(psz_var_domain);
            free(psz_decoded_path);
            vlc_UrlClean(&url);
            return VLC_ENOMEM;
        }

        if (smbc_stat(uri, &st) == 0)
        {
            is_dir = S_ISDIR(st.st_mode) != 0;
            size = st.st_size;
            break;
        }

        /* smbc_stat() fails with servers or shares. Assume directory. */
        is_dir = true;
        size = 0;

        if (errno != EACCES)
            break;

        errno = 0;
        if (!vlc_credential_get(&credential, access, "smb-user",
                                "smb-pwd", SMB_LOGIN_DIALOG_TITLE,
                                SMB_LOGIN_DIALOG_TEXT, url.psz_host))
            break;
    }

    vlc_credential_store(&credential, access);
    vlc_credential_clean(&credential);
    free(psz_var_domain);
    free(psz_decoded_path);

    /* Init access */
    access_sys_t *sys = vlc_obj_calloc(obj, 1, sizeof (*sys));
    if (unlikely(sys == NULL))
    {
        free(uri);
        vlc_UrlClean(&url);
        return VLC_ENOMEM;
    }

    access->p_sys = sys;

    if (is_dir)
    {
        sys->url = url;
        access->pf_readdir = DirRead;
        access->pf_control = access_vaDirectoryControlHelper;
        fd = smbc_opendir(uri);
        if (fd < 0)
            vlc_UrlClean(&sys->url);
    }
    else
    {
        access->pf_read = Read;
        access->pf_control = Control;
        access->pf_seek = Seek;
        fd = smbc_open(uri, O_RDONLY, 0);
        vlc_UrlClean(&url);
    }
    free(uri);

    if (fd < 0)
    {
        msg_Err(obj, "cannot open %s: %s",
                access->psz_location, vlc_strerror_c(errno));
        return VLC_EGENERIC;
    }

    sys->size = size;
    sys->i_smb = fd;

    return VLC_SUCCESS;
}