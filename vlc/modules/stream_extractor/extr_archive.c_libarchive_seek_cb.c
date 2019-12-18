#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  libarchive_t ;
struct TYPE_2__ {int /*<<< orphan*/ * p_source; } ;
typedef  TYPE_1__ libarchive_callback_t ;
typedef  scalar_t__ la_int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FATAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ stream_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static la_int64_t libarchive_seek_cb( libarchive_t* p_arc, void* p_obj,
  la_int64_t offset, int whence )
{
    VLC_UNUSED( p_arc );

    libarchive_callback_t* p_cb = (libarchive_callback_t*)p_obj;
    stream_t* p_source = p_cb->p_source;

    ssize_t whence_pos;

    switch( whence )
    {
        case SEEK_SET: whence_pos = 0;                           break;
        case SEEK_CUR: whence_pos = vlc_stream_Tell( p_source ); break;
        case SEEK_END: whence_pos = stream_Size( p_source ); break;
              default: vlc_assert_unreachable();

    }

    if( whence_pos < 0 || vlc_stream_Seek( p_source, whence_pos + offset ) )
        return ARCHIVE_FATAL;

    return vlc_stream_Tell( p_source );
}