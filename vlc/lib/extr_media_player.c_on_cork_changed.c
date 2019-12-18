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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_4__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaPlayerCorked ; 
 int /*<<< orphan*/  libvlc_MediaPlayerUncorked ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
on_cork_changed(vlc_player_t *player, unsigned cork_count, void *data)
{
    (void) player;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    event.type = cork_count ? libvlc_MediaPlayerCorked
                            : libvlc_MediaPlayerUncorked;

    libvlc_event_send(&mp->event_manager, &event);
}