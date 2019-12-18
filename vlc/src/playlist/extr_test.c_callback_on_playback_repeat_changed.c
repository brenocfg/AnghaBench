#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct playback_repeat_changed_report {int repeat; } ;
struct callback_ctx {int /*<<< orphan*/  vec_playback_repeat_changed; } ;
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (int /*<<< orphan*/ *,struct playback_repeat_changed_report) ; 

__attribute__((used)) static void
callback_on_playback_repeat_changed(vlc_playlist_t *playlist,
                                    enum vlc_playlist_playback_repeat repeat,
                                    void *userdata)
{
    VLC_UNUSED(playlist);
    struct callback_ctx *ctx = userdata;

    struct playback_repeat_changed_report report;
    report.repeat = repeat;
    vlc_vector_push(&ctx->vec_playback_repeat_changed, report);
}