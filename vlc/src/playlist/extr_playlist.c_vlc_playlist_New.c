#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int current; int has_prev; int has_next; int auto_preparse; int /*<<< orphan*/ * libvlc; scalar_t__ idgen; int /*<<< orphan*/  order; int /*<<< orphan*/  repeat; int /*<<< orphan*/  listeners; int /*<<< orphan*/  randomizer; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL ; 
 int /*<<< orphan*/  VLC_PLAYLIST_PLAYBACK_REPEAT_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  randomizer_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_object_instance (int /*<<< orphan*/ *) ; 
 int vlc_playlist_PlayerInit (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_init (int /*<<< orphan*/ *) ; 

vlc_playlist_t *
vlc_playlist_New(vlc_object_t *parent)
{
    vlc_playlist_t *playlist = malloc(sizeof(*playlist));
    if (unlikely(!playlist))
        return NULL;

    bool ok = vlc_playlist_PlayerInit(playlist, parent);
    if (unlikely(!ok))
    {
        free(playlist);
        return NULL;
    }

    vlc_vector_init(&playlist->items);
    randomizer_Init(&playlist->randomizer);
    playlist->current = -1;
    playlist->has_prev = false;
    playlist->has_next = false;
    vlc_list_init(&playlist->listeners);
    playlist->repeat = VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;
    playlist->order = VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL;
    playlist->idgen = 0;
#ifdef TEST_PLAYLIST
    playlist->libvlc = NULL;
    playlist->auto_preparse = false;
#else
    assert(parent);
    playlist->libvlc = vlc_object_instance(parent);
    playlist->auto_preparse = var_InheritBool(parent, "auto-preparse");
#endif

    return playlist;
}