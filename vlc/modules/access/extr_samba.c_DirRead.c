#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {int dummy; } ;
struct smbc_dirent {char* name; int smbc_type; } ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_6__ {char* psz_host; char* psz_path; } ;
struct TYPE_8__ {TYPE_1__ url; int /*<<< orphan*/  i_smb; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_NET ; 
 int ITEM_TYPE_DIRECTORY ; 
 int ITEM_TYPE_FILE ; 
#define  SMBC_COMMS_SHARE 136 
#define  SMBC_DIR 135 
#define  SMBC_FILE 134 
#define  SMBC_FILE_SHARE 133 
#define  SMBC_IPC_SHARE 132 
#define  SMBC_LINK 131 
#define  SMBC_PRINTER_SHARE 130 
#define  SMBC_SERVER 129 
#define  SMBC_WORKGROUP 128 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* smb_get_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char*) ; 
 struct smbc_dirent* smbc_readdir (int /*<<< orphan*/ ) ; 
 int vlc_readdir_helper_additem (struct vlc_readdir_helper*,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_readdir_helper_finish (struct vlc_readdir_helper*,int) ; 
 int /*<<< orphan*/  vlc_readdir_helper_init (struct vlc_readdir_helper*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* vlc_uri_encode (char const*) ; 

__attribute__((used)) static int DirRead (stream_t *p_access, input_item_node_t *p_node )
{
    access_sys_t *p_sys = p_access->p_sys;
    int i_ret = VLC_SUCCESS;

    struct vlc_readdir_helper rdh;
    vlc_readdir_helper_init( &rdh, p_access, p_node );

    struct smbc_dirent *p_entry;

    while( i_ret == VLC_SUCCESS && ( p_entry = smbc_readdir( p_sys->i_smb ) ) )
    {
        const char *psz_server = p_sys->url.psz_host;
        const char *psz_path = p_sys->url.psz_path;
        const char *psz_name = p_entry->name;
        int i_type;

        switch( p_entry->smbc_type )
        {
        case SMBC_SERVER:
        case SMBC_WORKGROUP:
            psz_server = p_sys->url.psz_host;
            psz_path = NULL;
            psz_name = NULL;
            /* fall through */
        case SMBC_FILE_SHARE:
        case SMBC_DIR:
            i_type = ITEM_TYPE_DIRECTORY;
            break;
        case SMBC_FILE:
            i_type = ITEM_TYPE_FILE;
            break;
        default:
        case SMBC_PRINTER_SHARE:
        case SMBC_COMMS_SHARE:
        case SMBC_IPC_SHARE:
        case SMBC_LINK:
            continue;
        }

        char *psz_encoded_name = NULL;
        if( psz_name != NULL
         && ( psz_encoded_name = vlc_uri_encode( psz_name ) ) == NULL )
        {
            i_ret = VLC_ENOMEM;
            break;
        }

        char *uri = smb_get_uri(NULL, NULL, NULL,
                                psz_server, psz_path, psz_encoded_name);
        if (uri == NULL) {
            free(psz_encoded_name);
            i_ret = VLC_ENOMEM;
            break;
        }
        free(psz_encoded_name);
        i_ret = vlc_readdir_helper_additem(&rdh, uri, NULL, p_entry->name,
                                           i_type, ITEM_NET);
        free(uri);
    }

    vlc_readdir_helper_finish( &rdh, i_ret == VLC_SUCCESS );

    return i_ret;
}