#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* psz_desc; TYPE_2__* psz_url; } ;
struct TYPE_8__ {struct TYPE_8__* p_pkey; TYPE_1__ release; int /*<<< orphan*/  lock; TYPE_3__* p_download; struct TYPE_8__* p_check; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ update_t ;
struct TYPE_9__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_3__*) ; 

void update_Delete( update_t *p_update )
{
    assert( p_update );

    if( p_update->p_check )
    {
        vlc_join( p_update->p_check->thread, NULL );
        free( p_update->p_check );
    }

    if( p_update->p_download )
    {
        atomic_store( &p_update->p_download->aborted, true );
        vlc_join( p_update->p_download->thread, NULL );
        vlc_object_delete(p_update->p_download);
    }

    vlc_mutex_destroy( &p_update->lock );

    free( p_update->release.psz_url );
    free( p_update->release.psz_desc );
    free( p_update->p_pkey );

    free( p_update );
}