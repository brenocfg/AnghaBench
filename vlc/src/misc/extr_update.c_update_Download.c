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
struct TYPE_8__ {TYPE_2__* p_download; int /*<<< orphan*/  p_libvlc; } ;
typedef  TYPE_1__ update_t ;
struct TYPE_9__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  aborted; int /*<<< orphan*/ * psz_destdir; TYPE_1__* p_update; } ;
typedef  TYPE_2__ update_download_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  update_DownloadReal ; 
 int /*<<< orphan*/  vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

void update_Download( update_t *p_update, const char *psz_destdir )
{
    assert( p_update );

    // If the object already exist, destroy it
    if( p_update->p_download )
    {
        atomic_store( &p_update->p_download->aborted, true );
        vlc_join( p_update->p_download->thread, NULL );
        vlc_object_delete(p_update->p_download);
    }

    update_download_thread_t *p_udt =
        vlc_custom_create( p_update->p_libvlc, sizeof( *p_udt ),
                           "update download" );
    if( !p_udt )
        return;

    p_udt->p_update = p_update;
    p_update->p_download = p_udt;
    p_udt->psz_destdir = psz_destdir ? strdup( psz_destdir ) : NULL;

    atomic_store(&p_udt->aborted, false);
    vlc_clone( &p_udt->thread, update_DownloadReal, p_udt, VLC_THREAD_PRIORITY_LOW );
}