#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_4__ {char* path; char* format; char* prefix_fmt; scalar_t__ is_sequential; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ vout_snapshot_save_cfg_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  cfg ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VoutOsdSnapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 
 scalar_t__ vout_GetSnapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* vout_snapshot_GetDirectory () ; 
 scalar_t__ vout_snapshot_SaveImage (char**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void VoutSaveSnapshot( vout_thread_t *p_vout )
{
    char *psz_path = var_InheritString( p_vout, "snapshot-path" );
    char *psz_format = var_InheritString( p_vout, "snapshot-format" );
    char *psz_prefix = var_InheritString( p_vout, "snapshot-prefix" );

    /* */
    picture_t *p_picture;
    block_t *p_image;

    /* 500ms timeout
     * XXX it will cause trouble with low fps video (< 2fps) */
    if( vout_GetSnapshot( p_vout, &p_image, &p_picture, NULL, psz_format, VLC_TICK_FROM_MS(500) ) )
    {
        p_picture = NULL;
        p_image = NULL;
        goto exit;
    }

    if( !psz_path )
    {
        psz_path = vout_snapshot_GetDirectory();
        if( !psz_path )
        {
            msg_Err( p_vout, "no path specified for snapshots" );
            goto exit;
        }
    }

    vout_snapshot_save_cfg_t cfg;
    memset( &cfg, 0, sizeof(cfg) );
    cfg.is_sequential = var_InheritBool( p_vout, "snapshot-sequential" );
    cfg.sequence = var_GetInteger( p_vout, "snapshot-num" );
    cfg.path = psz_path;
    cfg.format = psz_format;
    cfg.prefix_fmt = psz_prefix;

    char *psz_filename;
    int  i_sequence;
    if (vout_snapshot_SaveImage( &psz_filename, &i_sequence,
                                 p_image, p_vout, &cfg ) )
        goto exit;
    if( cfg.is_sequential )
        var_SetInteger( p_vout, "snapshot-num", i_sequence + 1 );

    VoutOsdSnapshot( p_vout, p_picture, psz_filename );

    /* signal creation of a new snapshot file */
    var_SetString( vlc_object_instance(p_vout), "snapshot-file", psz_filename );

    free( psz_filename );

exit:
    if( p_image )
        block_Release( p_image );
    if( p_picture )
        picture_Release( p_picture );
    free( psz_prefix );
    free( psz_format );
    free( psz_path );
}