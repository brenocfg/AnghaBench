#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  subitems_lock; TYPE_2__* p_subitems; int /*<<< orphan*/  p_libvlc_instance; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_7__ {int b_read_only; TYPE_1__* p_internal_md; } ;
typedef  TYPE_2__ libvlc_media_list_t ;

/* Variables and functions */
 TYPE_2__* libvlc_media_list_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libvlc_media_list_t *media_get_subitems( libvlc_media_t * p_md,
                                                bool b_create )
{
    libvlc_media_list_t *p_subitems = NULL;

    vlc_mutex_lock( &p_md->subitems_lock );
    if( p_md->p_subitems == NULL && b_create )
    {
        p_md->p_subitems = libvlc_media_list_new( p_md->p_libvlc_instance );
        if( p_md->p_subitems != NULL )
        {
            p_md->p_subitems->b_read_only = true;
            p_md->p_subitems->p_internal_md = p_md;
        }
    }
    p_subitems = p_md->p_subitems;
    vlc_mutex_unlock( &p_md->subitems_lock );
    return p_subitems;
}