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
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int workshop_get_font_height () ; 

void
adjust_sign_name(char *filename)
{
	char *s;
	static int fontSize = -1;

	if (fontSize == -1)
		fontSize = workshop_get_font_height();
	if (fontSize == 0)
		return;
	if (filename[0] == '-')
		return;

	/* This is ugly: later we should instead pass the fontheight over
	 * to eserve on startup and let eserve just send the right filenames
	 * to us in the first place

	 * I know that the filename will end with 1.xpm (see
	 * GuiEditor.cc`LispPrintSign if you wonder why) */
	s = filename+strlen(filename)-5;
	if (fontSize <= 11)
		strcpy(s, "2.xpm");
	else if (fontSize <= 15)
		strcpy(s, "1.xpm");
	else
		strcpy(s, ".xpm");
}