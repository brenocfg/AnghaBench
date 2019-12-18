#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vlc_readdir_helper {int dummy; } ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_9__ {char* psz_path; int /*<<< orphan*/  i_port; int /*<<< orphan*/  psz_host; } ;
struct TYPE_8__ {scalar_t__ b_mlst; } ;
struct TYPE_11__ {scalar_t__ tlsmode; TYPE_2__ url; TYPE_1__ features; int /*<<< orphan*/ * data; int /*<<< orphan*/  out; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 scalar_t__ IMPLICIT ; 
 int /*<<< orphan*/  ITEM_NET ; 
 int ITEM_TYPE_DIRECTORY ; 
 int ITEM_TYPE_FILE ; 
 int ITEM_TYPE_UNKNOWN ; 
 scalar_t__ NONE ; 
 int VLC_SUCCESS ; 
 int asprintf (char**,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strstr (char*,char*) ; 
 int vlc_readdir_helper_additem (struct vlc_readdir_helper*,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_readdir_helper_finish (struct vlc_readdir_helper*,int) ; 
 int /*<<< orphan*/  vlc_readdir_helper_init (struct vlc_readdir_helper*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* vlc_tls_GetLine (int /*<<< orphan*/ *) ; 
 char* vlc_uri_encode (char*) ; 

__attribute__((used)) static int DirRead (stream_t *p_access, input_item_node_t *p_current_node)
{
    access_sys_t *p_sys = p_access->p_sys;
    int i_ret = VLC_SUCCESS;

    assert( p_sys->data != NULL );
    assert( !p_sys->out );

    struct vlc_readdir_helper rdh;
    vlc_readdir_helper_init( &rdh, p_access, p_current_node );

    while (i_ret == VLC_SUCCESS)
    {
        char *psz_file;
        int type = ITEM_TYPE_UNKNOWN;

        char *psz_line = vlc_tls_GetLine( p_sys->data );
        if( psz_line == NULL )
            break;

        if( p_sys->features.b_mlst )
        {
            /* MLST Format is key=val;key=val...; FILENAME */
            if( strstr( psz_line, "type=dir" ) )
                type = ITEM_TYPE_DIRECTORY;
            if( strstr( psz_line, "type=file" ) )
                type = ITEM_TYPE_FILE;

            /* Get the filename or fail */
            psz_file = strchr( psz_line, ' ' );
            if( psz_file )
                psz_file++;
            else
            {
                msg_Warn( p_access, "Empty filename in MLST list" );
                free( psz_line );
                continue;
            }
        }
        else
            psz_file = psz_line;

        char *psz_uri;
        char *psz_filename = vlc_uri_encode( psz_file );
        if( psz_filename != NULL &&
            asprintf( &psz_uri, "%s://%s:%d%s%s/%s",
                      ( p_sys->tlsmode == NONE ) ? "ftp" :
                      ( ( p_sys->tlsmode == IMPLICIT ) ? "ftps" : "ftpes" ),
                      p_sys->url.psz_host, p_sys->url.i_port,
                      p_sys->url.psz_path ? "/" : "",
                      p_sys->url.psz_path ? p_sys->url.psz_path : "",
                      psz_filename ) != -1 )
        {
            i_ret = vlc_readdir_helper_additem( &rdh, psz_uri, NULL, psz_file,
                                                type, ITEM_NET );
            free( psz_uri );
        }
        free( psz_filename );
        free( psz_line );
    }

    vlc_readdir_helper_finish( &rdh, i_ret == VLC_SUCCESS );
    return i_ret;
}