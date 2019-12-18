#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libarchive_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_source; int /*<<< orphan*/  psz_url; TYPE_1__* p_sys; } ;
typedef  TYPE_2__ libarchive_callback_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_obj; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ libarchive_exit_cb (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * vlc_stream_NewURL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libarchive_jump_cb( libarchive_t* p_arc, void* p_obj_current,
  void* p_obj_next )
{
    libarchive_callback_t* p_current = (libarchive_callback_t*)p_obj_current;
    libarchive_callback_t* p_next    = (libarchive_callback_t*)p_obj_next;

    if( libarchive_exit_cb( p_arc, p_current ) )
        return ARCHIVE_FATAL;

    if( p_next->p_source == NULL )
        p_next->p_source = vlc_stream_NewURL( p_next->p_sys->p_obj,
                                              p_next->psz_url );

    return p_next->p_source ? ARCHIVE_OK : ARCHIVE_FATAL;
}