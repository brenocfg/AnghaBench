#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int guint ;
typedef  scalar_t__ guicolor_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {int char_width; int char_height; int /*<<< orphan*/  toolbar_h; int /*<<< orphan*/  menubar_h; int /*<<< orphan*/  mainwin; int /*<<< orphan*/  drawarea; int /*<<< orphan*/  formwin; scalar_t__ def_back_pixel; scalar_t__ def_norm_pixel; int /*<<< orphan*/ * geom; } ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  GO_MENUS ; 
 int /*<<< orphan*/  GO_TOOLBAR ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ *) ; 
 int HeightValue ; 
 scalar_t__ INVALCOLOR ; 
 int OK ; 
 int Rows ; 
 int TOOLBAR_ICONS ; 
 int TOOLBAR_TEXT ; 
 int WidthValue ; 
 int XNegative ; 
 int XParseGeometry (char*,int*,int*,unsigned int*,unsigned int*) ; 
 int XValue ; 
 int YNegative ; 
 int YValue ; 
 int /*<<< orphan*/ * background_argument ; 
 int /*<<< orphan*/  check_startup_plug_hints ; 
 int /*<<< orphan*/  drag_data_received_cb ; 
 int /*<<< orphan*/ * foreground_argument ; 
 int /*<<< orphan*/  form_configure_event ; 
 scalar_t__ found_iconic_arg ; 
 scalar_t__ found_reverse_arg ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_random_int () ; 
 unsigned long g_signal_connect_after (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_handler_disconnect (int /*<<< orphan*/ ,unsigned long) ; 
 char* g_strdup_printf (char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_menu_tool_height () ; 
 int get_menu_tool_width () ; 
 int /*<<< orphan*/  gtk_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_socket_id ; 
 int /*<<< orphan*/  gtk_widget_hide ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_move (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_resize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_window_set_role (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_check_colors () ; 
 scalar_t__ gui_get_base_height () ; 
 scalar_t__ gui_get_base_width () ; 
 scalar_t__ gui_get_color (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gui_gtk_set_dnd_targets () ; 
 int /*<<< orphan*/  gui_mch_get_screen_dimensions (int*,int*) ; 
 int /*<<< orphan*/  gui_mch_iconify () ; 
 int gui_win_x ; 
 int gui_win_y ; 
 int /*<<< orphan*/  hangul_keyboard_set () ; 
 int /*<<< orphan*/  highlight_gui_started () ; 
 int init_window_hints_state ; 
 int /*<<< orphan*/  limit_screen_size () ; 
 int /*<<< orphan*/  mainwin_destroy_cb ; 
 scalar_t__ mch_get_pid () ; 
 int /*<<< orphan*/  option_was_set (int /*<<< orphan*/ *) ; 
 int p_ghr ; 
 int /*<<< orphan*/  p_go ; 
 long p_window ; 
 char* role_argument ; 
 int /*<<< orphan*/  set_normal_colors () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int toolbar_flags ; 
 int /*<<< orphan*/  update_window_manager_hints (int,int) ; 
 scalar_t__ using_gnome ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gui_mch_open(void)
{
    guicolor_T fg_pixel = INVALCOLOR;
    guicolor_T bg_pixel = INVALCOLOR;
    guint		pixel_width;
    guint		pixel_height;

    /*
     * Allow setting a window role on the command line, or invent one
     * if none was specified.  This is mainly useful for GNOME session
     * support; allowing the WM to restore window placement.
     */
    if (role_argument != NULL)
    {
	gtk_window_set_role(GTK_WINDOW(gui.mainwin), role_argument);
    }
    else
    {
	char *role;

	/* Invent a unique-enough ID string for the role */
	role = g_strdup_printf("vim-%u-%u-%u",
			       (unsigned)mch_get_pid(),
			       (unsigned)g_random_int(),
			       (unsigned)time(NULL));

	gtk_window_set_role(GTK_WINDOW(gui.mainwin), role);
	g_free(role);
    }

    if (gui_win_x != -1 && gui_win_y != -1)
	gtk_window_move(GTK_WINDOW(gui.mainwin), gui_win_x, gui_win_y);

    /* Determine user specified geometry, if present. */
    if (gui.geom != NULL)
    {
	int		mask;
	unsigned int	w, h;
	int		x = 0;
	int		y = 0;

	mask = XParseGeometry((char *)gui.geom, &x, &y, &w, &h);

	if (mask & WidthValue)
	    Columns = w;
	if (mask & HeightValue)
	{
	    if (p_window > (long)h - 1 || !option_was_set((char_u *)"window"))
		p_window = h - 1;
	    Rows = h;
	}
	limit_screen_size();

	pixel_width = (guint)(gui_get_base_width() + Columns * gui.char_width);
	pixel_height = (guint)(gui_get_base_height() + Rows * gui.char_height);

	pixel_width  += get_menu_tool_width();
	pixel_height += get_menu_tool_height();

	if (mask & (XValue | YValue))
	{
	    int ww, hh;
	    gui_mch_get_screen_dimensions(&ww, &hh);
	    hh += p_ghr + get_menu_tool_height();
	    ww += get_menu_tool_width();
	    if (mask & XNegative)
		x += ww - pixel_width;
	    if (mask & YNegative)
		y += hh - pixel_height;
	    gtk_window_move(GTK_WINDOW(gui.mainwin), x, y);
	}
	vim_free(gui.geom);
	gui.geom = NULL;

	/* From now until everyone's stopped trying to set the window hints
	 * to their correct minimum values, stop them being set as we need
	 * them to remain at our required size for the parent GtkSocket to
	 * give us the right initial size.
	 */
	if (gtk_socket_id != 0  &&  (mask & WidthValue || mask & HeightValue))
	{
	    update_window_manager_hints(pixel_width, pixel_height);
	    init_window_hints_state = 1;
	    g_timeout_add(1000, check_startup_plug_hints, NULL);
	}
    }

    pixel_width = (guint)(gui_get_base_width() + Columns * gui.char_width);
    pixel_height = (guint)(gui_get_base_height() + Rows * gui.char_height);
    /* For GTK2 changing the size of the form widget doesn't cause window
     * resizing. */
    if (gtk_socket_id == 0)
	gtk_window_resize(GTK_WINDOW(gui.mainwin), pixel_width, pixel_height);
    update_window_manager_hints(0, 0);

    if (foreground_argument != NULL)
	fg_pixel = gui_get_color((char_u *)foreground_argument);
    if (fg_pixel == INVALCOLOR)
	fg_pixel = gui_get_color((char_u *)"Black");

    if (background_argument != NULL)
	bg_pixel = gui_get_color((char_u *)background_argument);
    if (bg_pixel == INVALCOLOR)
	bg_pixel = gui_get_color((char_u *)"White");

    if (found_reverse_arg)
    {
	gui.def_norm_pixel = bg_pixel;
	gui.def_back_pixel = fg_pixel;
    }
    else
    {
	gui.def_norm_pixel = fg_pixel;
	gui.def_back_pixel = bg_pixel;
    }

    /* Get the colors from the "Normal" and "Menu" group (set in syntax.c or
     * in a vimrc file) */
    set_normal_colors();

    /* Check that none of the colors are the same as the background color */
    gui_check_colors();

    /* Get the colors for the highlight groups (gui_check_colors() might have
     * changed them). */
    highlight_gui_started();	/* re-init colors and fonts */

    gtk_signal_connect(GTK_OBJECT(gui.mainwin), "destroy",
		       GTK_SIGNAL_FUNC(mainwin_destroy_cb), NULL);

#ifdef FEAT_HANGULIN
    hangul_keyboard_set();
#endif

    /*
     * Notify the fixed area about the need to resize the contents of the
     * gui.formwin, which we use for random positioning of the included
     * components.
     *
     * We connect this signal deferred finally after anything is in place,
     * since this is intended to handle resizements coming from the window
     * manager upon us and should not interfere with what VIM is requesting
     * upon startup.
     */
    gtk_signal_connect(GTK_OBJECT(gui.formwin), "configure_event",
		       GTK_SIGNAL_FUNC(form_configure_event), NULL);

#ifdef FEAT_DND
    /* Set up for receiving DND items. */
    gui_gtk_set_dnd_targets();

    gtk_signal_connect(GTK_OBJECT(gui.drawarea), "drag_data_received",
		       GTK_SIGNAL_FUNC(drag_data_received_cb), NULL);
#endif

	/* With GTK+ 2, we need to iconify the window before calling show()
	 * to avoid mapping the window for a short time. */
	if (found_iconic_arg && gtk_socket_id == 0)
	    gui_mch_iconify();

    {
#if defined(FEAT_GUI_GNOME) && defined(FEAT_MENU)
	unsigned long menu_handler = 0;
# ifdef FEAT_TOOLBAR
	unsigned long tool_handler = 0;
# endif
	/*
	 * Urgh hackish :/  For some reason BonoboDockLayout always forces a
	 * show when restoring the saved layout configuration.	We can't just
	 * hide the widgets again after gtk_widget_show(gui.mainwin) since it's
	 * a toplevel window and thus will be realized immediately.  Instead,
	 * connect signal handlers to hide the widgets just after they've been
	 * marked visible, but before the main window is realized.
	 */
	if (using_gnome && vim_strchr(p_go, GO_MENUS) == NULL)
	    menu_handler = g_signal_connect_after(gui.menubar_h, "show",
						  G_CALLBACK(&gtk_widget_hide),
						  NULL);
# ifdef FEAT_TOOLBAR
	if (using_gnome && vim_strchr(p_go, GO_TOOLBAR) == NULL
		&& (toolbar_flags & (TOOLBAR_TEXT | TOOLBAR_ICONS)))
	    tool_handler = g_signal_connect_after(gui.toolbar_h, "show",
						  G_CALLBACK(&gtk_widget_hide),
						  NULL);
# endif
#endif
	gtk_widget_show(gui.mainwin);

#if defined(FEAT_GUI_GNOME) && defined(FEAT_MENU)
	if (menu_handler != 0)
	    g_signal_handler_disconnect(gui.menubar_h, menu_handler);
# ifdef FEAT_TOOLBAR
	if (tool_handler != 0)
	    g_signal_handler_disconnect(gui.toolbar_h, tool_handler);
# endif
#endif
    }

    return OK;
}