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
struct TYPE_7__ {scalar_t__ i_count; } ;
struct TYPE_6__ {int b_read_only; int i_refcount; int /*<<< orphan*/ * p_internal_md; int /*<<< orphan*/ * p_md; TYPE_2__ items; int /*<<< orphan*/  refcount_lock; int /*<<< orphan*/  object_lock; int /*<<< orphan*/  event_manager; int /*<<< orphan*/ * p_libvlc_instance; } ;
typedef  TYPE_1__ libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libvlc_event_manager_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  libvlc_retain (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

libvlc_media_list_t *
libvlc_media_list_new( libvlc_instance_t * p_inst )
{
    libvlc_media_list_t * p_mlist;

    p_mlist = malloc(sizeof(libvlc_media_list_t));
    if( unlikely(p_mlist == NULL) )
    {
        libvlc_printerr( "Not enough memory" );
        return NULL;
    }

    p_mlist->p_libvlc_instance = p_inst;
    libvlc_event_manager_init( &p_mlist->event_manager, p_mlist );
    p_mlist->b_read_only = false;

    vlc_mutex_init( &p_mlist->object_lock );
    vlc_mutex_init( &p_mlist->refcount_lock ); // FIXME: spinlock?

    vlc_array_init( &p_mlist->items );
    assert( p_mlist->items.i_count == 0 );
    p_mlist->i_refcount = 1;
    p_mlist->p_md = NULL;
    p_mlist->p_internal_md = NULL;

    libvlc_retain( p_inst );
    return p_mlist;
}