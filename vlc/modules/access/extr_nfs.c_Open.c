#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_18__ {void* pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  psz_url; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_16__ {int i_count; int /*<<< orphan*/ * ppsz_names; } ;
struct TYPE_17__ {TYPE_1__ exports; } ;
struct TYPE_20__ {scalar_t__ psz_option; } ;
struct TYPE_19__ {int b_auto_guid; TYPE_10__* p_nfs_url; int /*<<< orphan*/ * p_mount; TYPE_2__ res; int /*<<< orphan*/ * p_nfs; int /*<<< orphan*/ * p_nfsdir; int /*<<< orphan*/ * p_nfsfh; int /*<<< orphan*/ * psz_url_decoded_slash; int /*<<< orphan*/ * psz_url_decoded; TYPE_8__ encoded_url; } ;
typedef  TYPE_4__ access_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/  server; int /*<<< orphan*/ * path; int /*<<< orphan*/ * file; } ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DirRead ; 
 void* FileControl ; 
 int /*<<< orphan*/  FileRead ; 
 int /*<<< orphan*/ * FileSeek ; 
 int /*<<< orphan*/  MountRead ; 
 int NfsInit (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 void* access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  mount_export_cb ; 
 scalar_t__ mount_getexports_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mount_getexports_finished_cb ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  nfs_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_destroy_url (TYPE_10__*) ; 
 scalar_t__ nfs_mount_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_mount_cb ; 
 int /*<<< orphan*/  nfs_mount_open_finished_cb ; 
 int /*<<< orphan*/  nfs_mount_open_slash_finished_cb ; 
 int /*<<< orphan*/ * rpc_init_context () ; 
 scalar_t__ strstr (scalar_t__,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_UrlParseFixup (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 scalar_t__ vlc_mount_mainloop (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_nfs_mainloop (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* vlc_obj_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * vlc_uri_decode_duplicate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Open(vlc_object_t *p_obj)
{
    stream_t *p_access = (stream_t *)p_obj;
    access_sys_t *p_sys = vlc_obj_calloc(p_obj, 1, sizeof (*p_sys));

    if (unlikely(p_sys == NULL))
        return VLC_ENOMEM;
    p_access->p_sys = p_sys;

    p_sys->b_auto_guid = var_InheritBool(p_obj, "nfs-auto-guid");

    /* nfs_* functions need a decoded url */
    p_sys->psz_url_decoded = vlc_uri_decode_duplicate(p_access->psz_url);
    if (p_sys->psz_url_decoded == NULL)
        goto error;

    /* Parse the encoded URL */
    if (vlc_UrlParseFixup(&p_sys->encoded_url, p_access->psz_url) != 0)
        goto error;
    if (p_sys->encoded_url.psz_option)
    {
        if (strstr(p_sys->encoded_url.psz_option, "uid")
         || strstr(p_sys->encoded_url.psz_option, "gid"))
            p_sys->b_auto_guid = false;
    }

    if (NfsInit(p_access, p_sys->psz_url_decoded) == -1)
        goto error;

    if (p_sys->p_nfs_url->path != NULL && p_sys->p_nfs_url->file != NULL)
    {
        /* The url has a valid path and file, mount the path and open/opendir
         * the file */
        msg_Dbg(p_access, "nfs_mount: server: '%s', path: '%s'",
                p_sys->p_nfs_url->server, p_sys->p_nfs_url->path);

        if (nfs_mount_async(p_sys->p_nfs, p_sys->p_nfs_url->server,
                            p_sys->p_nfs_url->path, nfs_mount_cb, p_access) < 0)
        {
            msg_Err(p_access, "nfs_mount_async failed");
            goto error;
        }

        if (vlc_nfs_mainloop(p_access, nfs_mount_open_finished_cb) < 0)
            goto error;

        if (p_sys->psz_url_decoded_slash != NULL)
        {
            /* Retry to mount by adding a '/' to the path, see comment in
             * nfs_mount_cb */
            nfs_destroy_url(p_sys->p_nfs_url);
            nfs_destroy_context(p_sys->p_nfs);
            p_sys->p_nfs_url = NULL;
            p_sys->p_nfs = NULL;

            if (NfsInit(p_access, p_sys->psz_url_decoded_slash) == -1
             || p_sys->p_nfs_url->path == NULL || p_sys->p_nfs_url->file == NULL)
                goto error;

            if (nfs_mount_async(p_sys->p_nfs, p_sys->p_nfs_url->server,
                                p_sys->p_nfs_url->path, nfs_mount_cb, p_access) < 0)
            {
                msg_Err(p_access, "nfs_mount_async failed");
                goto error;
            }

            if (vlc_nfs_mainloop(p_access, nfs_mount_open_slash_finished_cb) < 0)
                goto error;
        }

        if (p_sys->p_nfsfh != NULL)
        {
            p_access->pf_read = FileRead;
            p_access->pf_seek = FileSeek;
            p_access->pf_control = FileControl;
        }
        else if (p_sys->p_nfsdir != NULL)
        {
            p_access->pf_readdir = DirRead;
            p_access->pf_seek = NULL;
            p_access->pf_control = access_vaDirectoryControlHelper;
        }
        else
            vlc_assert_unreachable();
    }
    else
    {
        /* url is just a server: fetch exports point */
        nfs_destroy_context(p_sys->p_nfs);
        p_sys->p_nfs = NULL;

        p_sys->p_mount = rpc_init_context();
        if (p_sys->p_mount == NULL)
        {
            msg_Err(p_access, "rpc_init_context failed");
            goto error;
        }

        p_sys->res.exports.ppsz_names = NULL;
        p_sys->res.exports.i_count = -1;

        if (mount_getexports_async(p_sys->p_mount, p_sys->p_nfs_url->server,
                                   mount_export_cb, p_access) < 0)
        {
            msg_Err(p_access, "mount_getexports_async failed");
            goto error;
        }

        if (vlc_mount_mainloop(p_access, mount_getexports_finished_cb) < 0)
            goto error;

        p_access->pf_readdir = MountRead;
        p_access->pf_seek = NULL;
        p_access->pf_control = access_vaDirectoryControlHelper;
    }

    return VLC_SUCCESS;

error:
    Close(p_obj);
    return VLC_EGENERIC;
}