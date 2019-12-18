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
 int /*<<< orphan*/  GDK_WINDOW_XID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_set_xwindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_player ; 

void player_widget_on_realize(GtkWidget *widget, gpointer data) {
    libvlc_media_player_set_xwindow(media_player, GDK_WINDOW_XID(gtk_widget_get_window(widget)));
}