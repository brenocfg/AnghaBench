#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ b_seekable_source; } ;
typedef  TYPE_1__ private_sys_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  libarchive_t ;
struct TYPE_4__ {TYPE_1__* p_sys; int /*<<< orphan*/ * p_source; } ;
typedef  TYPE_2__ libarchive_callback_t ;
typedef  scalar_t__ la_int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FATAL ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static la_int64_t libarchive_skip_cb( libarchive_t* p_arc, void* p_obj,
  off_t i_request )
{
    VLC_UNUSED( p_arc );

    libarchive_callback_t* p_cb = (libarchive_callback_t*)p_obj;

    stream_t*  p_source = p_cb->p_source;
    private_sys_t* p_sys = p_cb->p_sys;

    /* TODO: fix b_seekable_source on libarchive_callback_t */

    if( p_sys->b_seekable_source )
    {
        if( vlc_stream_Seek( p_source, vlc_stream_Tell( p_source ) + i_request ) )
            return ARCHIVE_FATAL;

        return i_request;
    }

    ssize_t i_read = vlc_stream_Read( p_source, NULL, i_request );
    return  i_read >= 0 ? i_read : ARCHIVE_FATAL;
}