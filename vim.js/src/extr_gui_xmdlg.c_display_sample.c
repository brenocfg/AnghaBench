#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XmString ;
typedef  int /*<<< orphan*/  XmFontList ;
typedef  int /*<<< orphan*/  XFontStruct ;
struct TYPE_3__ {int /*<<< orphan*/  old_list; int /*<<< orphan*/ * old; int /*<<< orphan*/  sample; int /*<<< orphan*/  font_name; int /*<<< orphan*/  dialog; } ;
typedef  TYPE_1__ SharedFontSelData ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Arg ;

/* Variables and functions */
 int /*<<< orphan*/  XFreeFont (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XLoadQueryFont (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmFontListFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNfontList ; 
 int /*<<< orphan*/  XmNlabelString ; 
 int /*<<< orphan*/  XmStringCreateLocalized (char*) ; 
 int /*<<< orphan*/  XmStringFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XtDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtSetArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtSetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gui_motif_create_fontlist (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_sample(SharedFontSelData *data)
{
    Arg		    args[2];
    int		    n;
    XFontStruct	*   font;
    XmFontList	    font_list;
    Display *	    display;
    XmString	    str;

    display = XtDisplay(data->dialog);
    font = XLoadQueryFont(display, data->font_name);
    font_list = gui_motif_create_fontlist(font);

    n = 0;
    str = XmStringCreateLocalized("AaBbZzYy 0123456789");
    XtSetArg(args[n], XmNlabelString, str); n++;
    XtSetArg(args[n], XmNfontList, font_list); n++;

    XtSetValues(data->sample, args, n);
    XmStringFree(str);

    if (data->old)
    {
	XFreeFont(display, data->old);
	XmFontListFree(data->old_list);
    }
    data->old = font;
    data->old_list = font_list;
}