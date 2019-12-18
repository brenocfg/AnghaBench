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
typedef  int /*<<< orphan*/  libarchive_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_source; TYPE_1__* p_sys; } ;
typedef  TYPE_2__ libarchive_callback_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_dead; int /*<<< orphan*/ * source; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libarchive_exit_cb( libarchive_t* p_arc, void* p_obj )
{
    VLC_UNUSED( p_arc );

    libarchive_callback_t* p_cb = (libarchive_callback_t*)p_obj;

    if( p_cb->p_sys->source == p_cb->p_source )
    {  /* DO NOT CLOSE OUR MOTHER STREAM */
        if( !p_cb->p_sys->b_dead && vlc_stream_Seek( p_cb->p_source, 0 ) )
            return ARCHIVE_FATAL;
    }
    else if( p_cb->p_source )
    {
        vlc_stream_Delete( p_cb->p_source );
        p_cb->p_source = NULL;
    }

    return ARCHIVE_OK;
}