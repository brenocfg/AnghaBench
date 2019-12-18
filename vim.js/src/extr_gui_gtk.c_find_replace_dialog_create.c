#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gfloat ;
typedef  int gboolean ;
typedef  scalar_t__ char_u ;
struct TYPE_12__ {int /*<<< orphan*/  action_area; int /*<<< orphan*/ * vbox; } ;
struct TYPE_11__ {int /*<<< orphan*/ * mainwin; } ;
struct TYPE_10__ {scalar_t__ vc_type; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dialog; int /*<<< orphan*/ * all; int /*<<< orphan*/ * replace; int /*<<< orphan*/ * find; int /*<<< orphan*/ * down; int /*<<< orphan*/ * up; int /*<<< orphan*/ * mcase; int /*<<< orphan*/ * wword; int /*<<< orphan*/ * what; int /*<<< orphan*/ * with; } ;
typedef  TYPE_1__ SharedFindReplace ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  CONV (int /*<<< orphan*/ ) ; 
 scalar_t__ CONV_NONE ; 
 int FALSE ; 
 int /*<<< orphan*/  FRD_FINDNEXT ; 
 int /*<<< orphan*/  FRD_REPLACE ; 
 int /*<<< orphan*/  FRD_REPLACEALL ; 
 int /*<<< orphan*/  FRD_R_FINDNEXT ; 
 int /*<<< orphan*/ * GINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CAN_DEFAULT ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 TYPE_6__* GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int GTK_EXPAND ; 
 int GTK_FILL ; 
 int /*<<< orphan*/  GTK_MISC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RADIO_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  GTK_STOCK_CLOSE ; 
 int /*<<< orphan*/  GTK_STOCK_CONVERT ; 
 int /*<<< orphan*/  GTK_STOCK_FIND ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET_SET_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 scalar_t__ NUL ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* create_image_button (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_activate_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_changed_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_key_press_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_replace_cb (int /*<<< orphan*/ ) ; 
 TYPE_1__ find_widgets ; 
 scalar_t__* get_find_dialog_text (scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  gtk_box_pack_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_from_stock (int /*<<< orphan*/ ) ; 
 void* gtk_check_button_new_with_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_dialog_new () ; 
 int /*<<< orphan*/  gtk_dialog_set_has_separator (TYPE_6__*,int) ; 
 void* gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_frame_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_hbox_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_misc_set_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_radio_button_group (int /*<<< orphan*/ ) ; 
 void* gtk_radio_button_new_with_label (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_signal_connect_after (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_signal_connect_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbutton_box_new () ; 
 int /*<<< orphan*/ * gtk_vseparator_new () ; 
 int /*<<< orphan*/  gtk_widget_grab_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_hide_on_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_destroy_with_parent (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_transient_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ gui ; 
 TYPE_2__ output_conv ; 
 int /*<<< orphan*/  p_ic ; 
 TYPE_1__ repl_widgets ; 
 scalar_t__* string_convert (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 

__attribute__((used)) static void
find_replace_dialog_create(char_u *arg, int do_replace)
{
    GtkWidget	*hbox;		/* main top down box */
    GtkWidget	*actionarea;
    GtkWidget	*table;
    GtkWidget	*tmp;
    GtkWidget	*vbox;
    gboolean	sensitive;
    SharedFindReplace *frdp;
    char_u	*entry_text;
    int		wword = FALSE;
    int		mcase = !p_ic;
    char_u	*conv_buffer = NULL;
#   define CONV(message) convert_localized_message(&conv_buffer, (message))

    frdp = (do_replace) ? (&repl_widgets) : (&find_widgets);

    /* Get the search string to use. */
    entry_text = get_find_dialog_text(arg, &wword, &mcase);

    if (entry_text != NULL && output_conv.vc_type != CONV_NONE)
    {
	char_u *old_text = entry_text;
	entry_text = string_convert(&output_conv, entry_text, NULL);
	vim_free(old_text);
    }

    /*
     * If the dialog already exists, just raise it.
     */
    if (frdp->dialog)
    {
	if (entry_text != NULL)
	{
	    gtk_entry_set_text(GTK_ENTRY(frdp->what), (char *)entry_text);
	    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(frdp->wword),
							     (gboolean)wword);
	    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(frdp->mcase),
							     (gboolean)mcase);
	}
	gtk_window_present(GTK_WINDOW(frdp->dialog));
	vim_free(entry_text);
	return;
    }

    frdp->dialog = gtk_dialog_new();
    gtk_dialog_set_has_separator(GTK_DIALOG(frdp->dialog), FALSE);
    gtk_window_set_transient_for(GTK_WINDOW(frdp->dialog), GTK_WINDOW(gui.mainwin));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(frdp->dialog), TRUE);

    if (do_replace)
    {
	gtk_window_set_title(GTK_WINDOW(frdp->dialog),
			     CONV(_("VIM - Search and Replace...")));
    }
    else
    {
	gtk_window_set_title(GTK_WINDOW(frdp->dialog),
			     CONV(_("VIM - Search...")));
    }

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(frdp->dialog)->vbox), hbox);

    if (do_replace)
	table = gtk_table_new(1024, 4, FALSE);
    else
	table = gtk_table_new(1024, 3, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox), table, TRUE, TRUE, 0);
    gtk_container_border_width(GTK_CONTAINER(table), 4);

    tmp = gtk_label_new(CONV(_("Find what:")));
    gtk_misc_set_alignment(GTK_MISC(tmp), (gfloat)0.0, (gfloat)0.5);
    gtk_table_attach(GTK_TABLE(table), tmp, 0, 1, 0, 1,
		     GTK_FILL, GTK_EXPAND, 2, 2);
    frdp->what = gtk_entry_new();
    sensitive = (entry_text != NULL && entry_text[0] != NUL);
    if (entry_text != NULL)
	gtk_entry_set_text(GTK_ENTRY(frdp->what), (char *)entry_text);
    gtk_signal_connect(GTK_OBJECT(frdp->what), "changed",
		       GTK_SIGNAL_FUNC(entry_changed_cb), frdp->dialog);
    gtk_signal_connect_after(GTK_OBJECT(frdp->what), "key_press_event",
				 GTK_SIGNAL_FUNC(find_key_press_event),
				 (gpointer) frdp);
    gtk_table_attach(GTK_TABLE(table), frdp->what, 1, 1024, 0, 1,
		     GTK_EXPAND | GTK_FILL, GTK_EXPAND, 2, 2);

    if (do_replace)
    {
	tmp = gtk_label_new(CONV(_("Replace with:")));
	gtk_misc_set_alignment(GTK_MISC(tmp), (gfloat)0.0, (gfloat)0.5);
	gtk_table_attach(GTK_TABLE(table), tmp, 0, 1, 1, 2,
			 GTK_FILL, GTK_EXPAND, 2, 2);
	frdp->with = gtk_entry_new();
	gtk_signal_connect(GTK_OBJECT(frdp->with), "activate",
			   GTK_SIGNAL_FUNC(find_replace_cb),
			   GINT_TO_POINTER(FRD_R_FINDNEXT));
	gtk_signal_connect_after(GTK_OBJECT(frdp->with), "key_press_event",
				 GTK_SIGNAL_FUNC(find_key_press_event),
				 (gpointer) frdp);
	gtk_table_attach(GTK_TABLE(table), frdp->with, 1, 1024, 1, 2,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND, 2, 2);

	/*
	 * Make the entry activation only change the input focus onto the
	 * with item.
	 */
	gtk_signal_connect(GTK_OBJECT(frdp->what), "activate",
			   GTK_SIGNAL_FUNC(entry_activate_cb), frdp->with);
    }
    else
    {
	/*
	 * Make the entry activation do the search.
	 */
	gtk_signal_connect(GTK_OBJECT(frdp->what), "activate",
			   GTK_SIGNAL_FUNC(find_replace_cb),
			   GINT_TO_POINTER(FRD_FINDNEXT));
    }

    /* whole word only button */
    frdp->wword = gtk_check_button_new_with_label(CONV(_("Match whole word only")));
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(frdp->wword),
							(gboolean)wword);
    if (do_replace)
	gtk_table_attach(GTK_TABLE(table), frdp->wword, 0, 1023, 2, 3,
			 GTK_FILL, GTK_EXPAND, 2, 2);
    else
	gtk_table_attach(GTK_TABLE(table), frdp->wword, 0, 1023, 1, 2,
			 GTK_FILL, GTK_EXPAND, 2, 2);

    /* match case button */
    frdp->mcase = gtk_check_button_new_with_label(CONV(_("Match case")));
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(frdp->mcase),
							     (gboolean)mcase);
    if (do_replace)
	gtk_table_attach(GTK_TABLE(table), frdp->mcase, 0, 1023, 3, 4,
			 GTK_FILL, GTK_EXPAND, 2, 2);
    else
	gtk_table_attach(GTK_TABLE(table), frdp->mcase, 0, 1023, 2, 3,
			 GTK_FILL, GTK_EXPAND, 2, 2);

    tmp = gtk_frame_new(CONV(_("Direction")));
    if (do_replace)
	gtk_table_attach(GTK_TABLE(table), tmp, 1023, 1024, 2, 4,
			 GTK_FILL, GTK_FILL, 2, 2);
    else
	gtk_table_attach(GTK_TABLE(table), tmp, 1023, 1024, 1, 3,
			 GTK_FILL, GTK_FILL, 2, 2);
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_border_width(GTK_CONTAINER(vbox), 0);
    gtk_container_add(GTK_CONTAINER(tmp), vbox);

    /* 'Up' and 'Down' buttons */
    frdp->up = gtk_radio_button_new_with_label(NULL, CONV(_("Up")));
    gtk_box_pack_start(GTK_BOX(vbox), frdp->up, TRUE, TRUE, 0);
    frdp->down = gtk_radio_button_new_with_label(
			gtk_radio_button_group(GTK_RADIO_BUTTON(frdp->up)),
			CONV(_("Down")));
    gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(frdp->down), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 2);
    gtk_box_pack_start(GTK_BOX(vbox), frdp->down, TRUE, TRUE, 0);

    /* vbox to hold the action buttons */
    actionarea = gtk_vbutton_box_new();
    gtk_container_border_width(GTK_CONTAINER(actionarea), 2);
    gtk_box_pack_end(GTK_BOX(hbox), actionarea, FALSE, FALSE, 0);

    /* 'Find Next' button */
    frdp->find = create_image_button(GTK_STOCK_FIND, _("Find Next"));
    gtk_widget_set_sensitive(frdp->find, sensitive);

    gtk_signal_connect(GTK_OBJECT(frdp->find), "clicked",
		       GTK_SIGNAL_FUNC(find_replace_cb),
		       (do_replace) ? GINT_TO_POINTER(FRD_R_FINDNEXT)
				    : GINT_TO_POINTER(FRD_FINDNEXT));

    GTK_WIDGET_SET_FLAGS(frdp->find, GTK_CAN_DEFAULT);
    gtk_box_pack_start(GTK_BOX(actionarea), frdp->find, FALSE, FALSE, 0);
    gtk_widget_grab_default(frdp->find);

    if (do_replace)
    {
	/* 'Replace' button */
	frdp->replace = create_image_button(GTK_STOCK_CONVERT, _("Replace"));
	gtk_widget_set_sensitive(frdp->replace, sensitive);
	GTK_WIDGET_SET_FLAGS(frdp->replace, GTK_CAN_DEFAULT);
	gtk_box_pack_start(GTK_BOX(actionarea), frdp->replace, FALSE, FALSE, 0);
	gtk_signal_connect(GTK_OBJECT(frdp->replace), "clicked",
			   GTK_SIGNAL_FUNC(find_replace_cb),
			   GINT_TO_POINTER(FRD_REPLACE));

	/* 'Replace All' button */
	frdp->all = create_image_button(GTK_STOCK_CONVERT, _("Replace All"));
	gtk_widget_set_sensitive(frdp->all, sensitive);
	GTK_WIDGET_SET_FLAGS(frdp->all, GTK_CAN_DEFAULT);
	gtk_box_pack_start(GTK_BOX(actionarea), frdp->all, FALSE, FALSE, 0);
	gtk_signal_connect(GTK_OBJECT(frdp->all), "clicked",
			   GTK_SIGNAL_FUNC(find_replace_cb),
			   GINT_TO_POINTER(FRD_REPLACEALL));
    }

    /* 'Cancel' button */
    tmp = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
    GTK_WIDGET_SET_FLAGS(tmp, GTK_CAN_DEFAULT);
    gtk_box_pack_end(GTK_BOX(actionarea), tmp, FALSE, FALSE, 0);
    gtk_signal_connect_object(GTK_OBJECT(tmp),
			      "clicked", GTK_SIGNAL_FUNC(gtk_widget_hide),
			      GTK_OBJECT(frdp->dialog));
    gtk_signal_connect_object(GTK_OBJECT(frdp->dialog),
			      "delete_event", GTK_SIGNAL_FUNC(gtk_widget_hide_on_delete),
			      GTK_OBJECT(frdp->dialog));

    tmp = gtk_vseparator_new();
    gtk_box_pack_end(GTK_BOX(hbox), tmp, FALSE, FALSE, 10);

    /* Suppress automatic show of the unused action area */
    gtk_widget_hide(GTK_DIALOG(frdp->dialog)->action_area);
    gtk_widget_show_all(hbox);
    gtk_widget_show(frdp->dialog);

    vim_free(entry_text);
    vim_free(conv_buffer);
#undef CONV
}