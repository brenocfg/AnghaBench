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

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_button_set_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_player ; 
 int /*<<< orphan*/  playpause_button ; 

void play(void) {
    libvlc_media_player_play(media_player);
    gtk_button_set_label(GTK_BUTTON(playpause_button), "gtk-media-pause");
}