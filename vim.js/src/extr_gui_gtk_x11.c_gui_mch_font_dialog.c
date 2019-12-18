#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ char_u ;
struct TYPE_6__ {int /*<<< orphan*/ * mainwin; } ;
struct TYPE_5__ {scalar_t__ vc_type; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 scalar_t__ CONV_NONE ; 
 char const* DEFAULT_FONT ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FONT_SELECTION_DIALOG (int /*<<< orphan*/ *) ; 
 int GTK_RESPONSE_NONE ; 
 int GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  STRCPY (scalar_t__*,char*) ; 
 int STRLEN (scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int gtk_dialog_run (int /*<<< orphan*/ ) ; 
 char* gtk_font_selection_dialog_get_font_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_font_selection_dialog_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_font_selection_dialog_set_font_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_destroy_with_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_transient_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ gui ; 
 TYPE_1__ input_conv ; 
 TYPE_1__ output_conv ; 
 scalar_t__* string_convert (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 
 int /*<<< orphan*/  vim_isdigit (scalar_t__) ; 
 scalar_t__* vim_strnsave (scalar_t__*,int) ; 
 scalar_t__* vim_strsave_escaped (scalar_t__*,scalar_t__*) ; 

char_u *
gui_mch_font_dialog(char_u *oldval)
{
    GtkWidget	*dialog;
    int		response;
    char_u	*fontname = NULL;
    char_u	*oldname;

    dialog = gtk_font_selection_dialog_new(NULL);

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(gui.mainwin));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);

    if (oldval != NULL && oldval[0] != NUL)
    {
	if (output_conv.vc_type != CONV_NONE)
	    oldname = string_convert(&output_conv, oldval, NULL);
	else
	    oldname = oldval;

	/* Annoying bug in GTK (or Pango): if the font name does not include a
	 * size, zero is used.  Use default point size ten. */
	if (!vim_isdigit(oldname[STRLEN(oldname) - 1]))
	{
	    char_u	*p = vim_strnsave(oldname, STRLEN(oldname) + 3);

	    if (p != NULL)
	    {
		STRCPY(p + STRLEN(p), " 10");
		if (oldname != oldval)
		    vim_free(oldname);
		oldname = p;
	    }
	}

	gtk_font_selection_dialog_set_font_name(
		GTK_FONT_SELECTION_DIALOG(dialog), (const char *)oldname);

	if (oldname != oldval)
	    vim_free(oldname);
    }
    else
	gtk_font_selection_dialog_set_font_name(
		GTK_FONT_SELECTION_DIALOG(dialog), DEFAULT_FONT);

    response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_OK)
    {
	char *name;

	name = gtk_font_selection_dialog_get_font_name(
			    GTK_FONT_SELECTION_DIALOG(dialog));
	if (name != NULL)
	{
	    char_u  *p;

	    /* Apparently some font names include a comma, need to escape
	     * that, because in 'guifont' it separates names. */
	    p = vim_strsave_escaped((char_u *)name, (char_u *)",");
	    g_free(name);
	    if (p != NULL && input_conv.vc_type != CONV_NONE)
	    {
		fontname = string_convert(&input_conv, p, NULL);
		vim_free(p);
	    }
	    else
		fontname = p;
	}
    }

    if (response != GTK_RESPONSE_NONE)
	gtk_widget_destroy(dialog);

    return fontname;
}