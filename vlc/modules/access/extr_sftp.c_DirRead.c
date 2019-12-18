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
struct vlc_readdir_helper {int dummy; } ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_10__ {int /*<<< orphan*/  psz_base_url; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ access_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  permissions; } ;
typedef  TYPE_3__ LIBSSH2_SFTP_ATTRIBUTES ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_NET ; 
 int ITEM_TYPE_DIRECTORY ; 
 int ITEM_TYPE_FILE ; 
 int LIBSSH2_ERROR_BUFFER_TOO_SMALL ; 
 int LIBSSH2_ERROR_EAGAIN ; 
 scalar_t__ LIBSSH2_SFTP_S_ISDIR (int /*<<< orphan*/ ) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int libssh2_sftp_readdir (int /*<<< orphan*/ ,char*,size_t,TYPE_3__*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int vlc_readdir_helper_additem (struct vlc_readdir_helper*,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_readdir_helper_finish (struct vlc_readdir_helper*,int) ; 
 int /*<<< orphan*/  vlc_readdir_helper_init (struct vlc_readdir_helper*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* vlc_uri_encode (char*) ; 

__attribute__((used)) static int DirRead (stream_t *p_access, input_item_node_t *p_current_node)
{
    access_sys_t *p_sys = p_access->p_sys;
    LIBSSH2_SFTP_ATTRIBUTES attrs;
    int i_ret = VLC_SUCCESS;
    int err;
    /* Allocate 1024 bytes for file name. Longer names are skipped.
     * libssh2 does not support seeking in directory streams.
     * Retrying with larger buffer is possible, but would require
     * re-opening the directory stream.
     */
    size_t i_size = 1024;
    char *psz_file = malloc( i_size );

    if( !psz_file )
        return VLC_ENOMEM;

    struct vlc_readdir_helper rdh;
    vlc_readdir_helper_init( &rdh, p_access, p_current_node );

    while( i_ret == VLC_SUCCESS
        && 0 != ( err = libssh2_sftp_readdir( p_sys->file, psz_file, i_size, &attrs ) ) )
    {
        if( err < 0 )
        {
            if( err == LIBSSH2_ERROR_BUFFER_TOO_SMALL )
            {
                /* seeking back is not possible ... */
                msg_Dbg( p_access, "skipped too long file name" );
                continue;
            }
            if( err == LIBSSH2_ERROR_EAGAIN )
            {
                continue;
            }
            msg_Err( p_access, "directory read failed" );
            break;
        }

        /* Create an input item for the current entry */

        char *psz_full_uri, *psz_uri;

        psz_uri = vlc_uri_encode( psz_file );
        if( psz_uri == NULL )
        {
            i_ret = VLC_ENOMEM;
            break;
        }

        if( asprintf( &psz_full_uri, "%s/%s", p_sys->psz_base_url, psz_uri ) == -1 )
        {
            free( psz_uri );
            i_ret = VLC_ENOMEM;
            break;
        }
        free( psz_uri );

        int i_type = LIBSSH2_SFTP_S_ISDIR( attrs.permissions ) ? ITEM_TYPE_DIRECTORY : ITEM_TYPE_FILE;
        i_ret = vlc_readdir_helper_additem( &rdh, psz_full_uri, NULL, psz_file,
                                            i_type, ITEM_NET );
        free( psz_full_uri );
    }

    vlc_readdir_helper_finish( &rdh, i_ret == VLC_SUCCESS );
    free( psz_file );
    return i_ret;
}