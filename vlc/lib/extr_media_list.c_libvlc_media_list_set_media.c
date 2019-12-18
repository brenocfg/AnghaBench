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
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_4__ {int /*<<< orphan*/  object_lock; int /*<<< orphan*/ * p_md; scalar_t__ p_internal_md; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlist_is_writable (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_media_list_set_media( libvlc_media_list_t * p_mlist,
                                  libvlc_media_t * p_md )

{
    vlc_mutex_lock( &p_mlist->object_lock );
    if( p_mlist->p_internal_md || !mlist_is_writable(p_mlist) )
    {
        vlc_mutex_unlock( &p_mlist->object_lock );
        return;
    }
    libvlc_media_release( p_mlist->p_md );
    libvlc_media_retain( p_md );
    p_mlist->p_md = p_md;
    vlc_mutex_unlock( &p_mlist->object_lock );
}