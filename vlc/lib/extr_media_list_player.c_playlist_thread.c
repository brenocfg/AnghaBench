#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ seek_offset; int /*<<< orphan*/  mp_callback_lock; int /*<<< orphan*/  seek_pending; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_relative_playlist_position_and_play (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *playlist_thread(void *data)
{
    libvlc_media_list_player_t *mlp = data;

    vlc_mutex_lock(&mlp->mp_callback_lock);
    mutex_cleanup_push(&mlp->mp_callback_lock);

    for (;;)
    {
        int canc;

        while (mlp->seek_offset == 0)
            vlc_cond_wait(&mlp->seek_pending, &mlp->mp_callback_lock);

        canc = vlc_savecancel();
        set_relative_playlist_position_and_play(mlp, mlp->seek_offset);
        mlp->seek_offset = 0;
        vlc_restorecancel(canc);
    }

    vlc_cleanup_pop();
    vlc_assert_unreachable();
}