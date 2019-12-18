#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_refcount; int /*<<< orphan*/  object_lock; int /*<<< orphan*/  mp_callback_lock; int /*<<< orphan*/  seek_pending; int /*<<< orphan*/  event_manager; int /*<<< orphan*/ * p_mi; int /*<<< orphan*/  thread; scalar_t__ seek_offset; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  install_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_event_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_manager_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_media_player_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  playlist_thread ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

libvlc_media_list_player_t *
libvlc_media_list_player_new(libvlc_instance_t * p_instance)
{
    libvlc_media_list_player_t * p_mlp;
    p_mlp = calloc( 1, sizeof(libvlc_media_list_player_t) );
    if (unlikely(p_mlp == NULL))
    {
        libvlc_printerr("Not enough memory");
        return NULL;
    }

    p_mlp->i_refcount = 1;
    p_mlp->seek_offset = 0;
    vlc_mutex_init(&p_mlp->object_lock);
    vlc_mutex_init(&p_mlp->mp_callback_lock);
    vlc_cond_init(&p_mlp->seek_pending);
    libvlc_event_manager_init(&p_mlp->event_manager, p_mlp);

    /* Create the underlying media_player */
    p_mlp->p_mi = libvlc_media_player_new(p_instance);
    if( p_mlp->p_mi == NULL )
        goto error;
    install_media_player_observer(p_mlp);

    if (vlc_clone(&p_mlp->thread, playlist_thread, p_mlp,
                  VLC_THREAD_PRIORITY_LOW))
    {
        libvlc_media_player_release(p_mlp->p_mi);
        goto error;
    }

    return p_mlp;
error:
    libvlc_event_manager_destroy(&p_mlp->event_manager);
    vlc_cond_destroy(&p_mlp->seek_pending);
    vlc_mutex_destroy(&p_mlp->mp_callback_lock);
    vlc_mutex_destroy(&p_mlp->object_lock);
    free(p_mlp);
    return NULL;
}