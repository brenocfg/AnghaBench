#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_3__ {int b_seekable_archive; int b_seekable_source; size_t i_callback_data; int /*<<< orphan*/  p_archive; int /*<<< orphan*/  p_obj; int /*<<< orphan*/ * pp_callback_data; } ;
typedef  TYPE_1__ private_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_read_append_callback_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_new () ; 
 scalar_t__ archive_read_open2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_read_set_seek_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_read_set_switch_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_format_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libarchive_exit_cb ; 
 int /*<<< orphan*/  libarchive_jump_cb ; 
 int /*<<< orphan*/  libarchive_read_cb ; 
 int /*<<< orphan*/  libarchive_seek_cb ; 
 int /*<<< orphan*/  libarchive_skip_cb ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_stream_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int archive_init( private_sys_t* p_sys, stream_t* source )
{
    /* CREATE ARCHIVE HANDLE */

    p_sys->p_archive = archive_read_new();

    if( unlikely( !p_sys->p_archive ) )
    {
        msg_Dbg( p_sys->p_obj, "unable to create libarchive handle" );
        return VLC_EGENERIC;
    }

    /* SETUP SEEKING */

    p_sys->b_seekable_archive = false;

    if( vlc_stream_Control( source, STREAM_CAN_SEEK,
        &p_sys->b_seekable_source ) )
    {
        msg_Warn( p_sys->p_obj, "unable to query whether source stream can seek" );
        p_sys->b_seekable_source = false;
    }

    if( p_sys->b_seekable_source )
    {
        if( archive_read_set_seek_callback( p_sys->p_archive,
            libarchive_seek_cb ) )
        {
            msg_Err( p_sys->p_obj, "archive_read_set_callback failed, aborting." );
            return VLC_EGENERIC;
        }
    }

    /* ENABLE ALL FORMATS/FILTERS */

    archive_read_support_filter_all( p_sys->p_archive );
    archive_read_support_format_all( p_sys->p_archive );

    /* REGISTER CALLBACK DATA */

    if( archive_read_set_switch_callback( p_sys->p_archive,
        libarchive_jump_cb ) )
    {
        msg_Err( p_sys->p_obj, "archive_read_set_switch_callback failed, aborting." );
        return VLC_EGENERIC;
    }

    for( size_t i = 0; i < p_sys->i_callback_data; ++i )
    {
        if( archive_read_append_callback_data( p_sys->p_archive,
            p_sys->pp_callback_data[i] ) )
        {
            return VLC_EGENERIC;
        }
    }

    /* OPEN THE ARCHIVE */

    if( archive_read_open2( p_sys->p_archive, p_sys->pp_callback_data[0], NULL,
        libarchive_read_cb, libarchive_skip_cb, libarchive_exit_cb ) )
    {
        msg_Dbg( p_sys->p_obj, "libarchive: %s",
          archive_error_string( p_sys->p_archive ) );

        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}