#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_input_item; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int b_error; int /*<<< orphan*/ * f; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_RECORD_PREFIX ; 
 int /*<<< orphan*/  VLC_DOWNLOAD_DIR ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 char* config_GetUserDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_CreateFilename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 char* var_CreateGetNonEmptyString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 

__attribute__((used)) static int Start( stream_t *s, const char *psz_extension )
{
    stream_sys_t *p_sys = s->p_sys;

    char *psz_file;
    FILE *f;

    /* */
    if( !psz_extension )
        psz_extension = "dat";

    /* Retreive path */
    char *psz_path = var_CreateGetNonEmptyString( s, "input-record-path" );
    if( !psz_path )
        psz_path = config_GetUserDir( VLC_DOWNLOAD_DIR );

    if( !psz_path )
        return VLC_ENOMEM;

    /* Create file name
     * TODO allow prefix configuration */
    psz_file = input_item_CreateFilename( s->p_input_item, psz_path,
                                          INPUT_RECORD_PREFIX, psz_extension );

    free( psz_path );

    if( !psz_file )
        return VLC_ENOMEM;

    f = vlc_fopen( psz_file, "wb" );
    if( !f )
    {
        free( psz_file );
        return VLC_EGENERIC;
    }

    /* signal new record file */
    var_SetString( vlc_object_instance(s), "record-file", psz_file );

    msg_Dbg( s, "Recording into %s", psz_file );
    free( psz_file );

    /* */
    p_sys->f = f;
    p_sys->b_error = false;
    return VLC_SUCCESS;
}