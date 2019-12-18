#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {int dummy; } ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/ * smb_stat_list ;
typedef  int /*<<< orphan*/ * smb_stat ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_tid; int /*<<< orphan*/  p_session; int /*<<< orphan*/ * psz_path; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int ITEM_TYPE_DIRECTORY ; 
 int ITEM_TYPE_FILE ; 
 int /*<<< orphan*/  SMB_STAT_ISDIR ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int add_item (TYPE_1__*,struct vlc_readdir_helper*,char const*,int) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * smb_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ smb_stat_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * smb_stat_list_at (int /*<<< orphan*/ *,size_t) ; 
 size_t smb_stat_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_stat_list_destroy (int /*<<< orphan*/ *) ; 
 char* smb_stat_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_readdir_helper_finish (struct vlc_readdir_helper*,int) ; 
 int /*<<< orphan*/  vlc_readdir_helper_init (struct vlc_readdir_helper*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int BrowseDirectory( stream_t *p_access, input_item_node_t *p_node )
{
    access_sys_t *p_sys = p_access->p_sys;
    smb_stat_list   files;
    smb_stat        st;
    char           *psz_query;
    const char     *psz_name;
    size_t          files_count;
    int             i_ret = VLC_SUCCESS;

    if( p_sys->psz_path != NULL )
    {
        if( asprintf( &psz_query, "%s\\*", p_sys->psz_path ) == -1 )
            return VLC_ENOMEM;
        files = smb_find( p_sys->p_session, p_sys->i_tid, psz_query );
        free( psz_query );
    }
    else
        files = smb_find( p_sys->p_session, p_sys->i_tid, "\\*" );

    if( files == NULL )
        return VLC_EGENERIC;

    struct vlc_readdir_helper rdh;
    vlc_readdir_helper_init( &rdh, p_access, p_node );

    files_count = smb_stat_list_count( files );
    for( size_t i = 0; i < files_count && i_ret == VLC_SUCCESS; i++ )
    {
        int i_type;

        st = smb_stat_list_at( files, i );

        if( st == NULL )
        {
            continue;
        }

        psz_name = smb_stat_name( st );

        i_type = smb_stat_get( st, SMB_STAT_ISDIR ) ?
                 ITEM_TYPE_DIRECTORY : ITEM_TYPE_FILE;
        i_ret = add_item( p_access, &rdh, psz_name, i_type );
    }

    vlc_readdir_helper_finish( &rdh, i_ret == VLC_SUCCESS );

    smb_stat_list_destroy( files );
    return i_ret;
}