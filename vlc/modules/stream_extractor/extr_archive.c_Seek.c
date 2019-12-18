#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_extractor_t ;
struct TYPE_9__ {int b_eof; scalar_t__ i_offset; int /*<<< orphan*/  p_archive; scalar_t__ b_dead; int /*<<< orphan*/  b_seekable_archive; int /*<<< orphan*/  p_entry; int /*<<< orphan*/  b_seekable_source; } ;
typedef  TYPE_2__ private_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ archive_entry_size (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_size_is_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_extractor_reset (TYPE_1__*) ; 
 scalar_t__ archive_seek_data (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_skip_decompressed (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static int Seek( stream_extractor_t* p_extractor, uint64_t i_req )
{
    private_sys_t* p_sys = p_extractor->p_sys;

    if( !p_sys->p_entry || !p_sys->b_seekable_source )
        return VLC_EGENERIC;

    if( archive_entry_size_is_set( p_sys->p_entry ) &&
        (uint64_t)archive_entry_size( p_sys->p_entry ) <= i_req )
    {
        p_sys->b_eof = true;
        return VLC_SUCCESS;
    }

    p_sys->b_eof = false;

    if( !p_sys->b_seekable_archive || p_sys->b_dead
      || archive_seek_data( p_sys->p_archive, i_req, SEEK_SET ) < 0 )
    {
        msg_Dbg( p_extractor,
            "intrinsic seek failed: '%s' (falling back to dumb seek)",
            archive_error_string( p_sys->p_archive ) );

        uint64_t i_skip = i_req - p_sys->i_offset;

        /* RECREATE LIBARCHIVE HANDLE IF WE ARE SEEKING BACKWARDS */

        if( i_req < p_sys->i_offset )
        {
            if( archive_extractor_reset( p_extractor ) )
            {
                msg_Err( p_extractor, "unable to reset libarchive handle" );
                return VLC_EGENERIC;
            }

            i_skip = i_req;
        }

        if( archive_skip_decompressed( p_extractor, i_skip ) )
            msg_Dbg( p_extractor, "failed to skip to seek position" );
    }

    p_sys->i_offset = i_req;
    return VLC_SUCCESS;
}