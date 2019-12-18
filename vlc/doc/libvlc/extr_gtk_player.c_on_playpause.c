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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int libvlc_media_player_is_playing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_player ; 
 int /*<<< orphan*/  pause_player () ; 
 int /*<<< orphan*/  play () ; 

void on_playpause(GtkWidget *widget, gpointer data) {
    if(libvlc_media_player_is_playing(media_player) == 1) {
        pause_player();
    }
    else {
        play();
    }
}