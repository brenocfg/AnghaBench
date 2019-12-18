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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  BORDER_WIDTH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BUTTONBOX_START ; 
 int /*<<< orphan*/  GTK_BUTTON_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_BAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MENU_SHELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_STOCK_MEDIA_STOP ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_button_box_set_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_from_stock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_button_set_use_stock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_drawing_area_new () ; 
 int /*<<< orphan*/ * gtk_hbutton_box_new () ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_menu_bar_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_menu_bar_new () ; 
 int /*<<< orphan*/ * gtk_menu_item_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_menu_item_set_submenu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_menu_new () ; 
 int /*<<< orphan*/  gtk_menu_shell_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_default_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  libvlc_media_player_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_player ; 
 int /*<<< orphan*/  on_open ; 
 int /*<<< orphan*/  on_playpause ; 
 int /*<<< orphan*/  on_stop ; 
 int /*<<< orphan*/  player_widget_on_realize ; 
 int /*<<< orphan*/ * playpause_button ; 
 int /*<<< orphan*/  vlc_inst ; 

int main( int argc, char *argv[] ) {
    GtkWidget *window,
              *vbox,
              *menubar,
              *filemenu,
              *fileitem,
              *filemenu_openitem,
              *player_widget,
              *hbuttonbox,
              *stop_button;
    
    gtk_init (&argc, &argv);
    // setup window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ libVLC Demo");

    //setup vbox
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //setup menu
    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();
    fileitem = gtk_menu_item_new_with_label ("File");
    filemenu_openitem = gtk_menu_item_new_with_label("Open");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), filemenu_openitem);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileitem), filemenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), fileitem);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    g_signal_connect(filemenu_openitem, "activate", G_CALLBACK(on_open), window);

    //setup player widget
    player_widget = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(vbox), player_widget, TRUE, TRUE, 0);

    //setup controls
    //playpause_button = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);
    playpause_button = gtk_button_new_with_label("gtk-media-play");
    gtk_button_set_use_stock(GTK_BUTTON(playpause_button), TRUE);
    stop_button = gtk_button_new_from_stock(GTK_STOCK_MEDIA_STOP);
    g_signal_connect(playpause_button, "clicked", G_CALLBACK(on_playpause), NULL);
    g_signal_connect(stop_button, "clicked", G_CALLBACK(on_stop), NULL);
    hbuttonbox = gtk_hbutton_box_new();
    gtk_container_set_border_width(GTK_CONTAINER(hbuttonbox), BORDER_WIDTH);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(hbuttonbox), GTK_BUTTONBOX_START);
    gtk_box_pack_start(GTK_BOX(hbuttonbox), playpause_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbuttonbox), stop_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbuttonbox, FALSE, FALSE, 0);

    //setup vlc
    vlc_inst = libvlc_new(0, NULL);
    media_player = libvlc_media_player_new(vlc_inst);
    g_signal_connect(G_OBJECT(player_widget), "realize", G_CALLBACK(player_widget_on_realize), NULL);

    gtk_widget_show_all(window);
    gtk_main ();

    libvlc_media_player_release(media_player);
    libvlc_release(vlc_inst);
    return 0;
}