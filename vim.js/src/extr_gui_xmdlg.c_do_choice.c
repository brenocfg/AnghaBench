#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum ListSpecifier { ____Placeholder_ListSpecifier } ListSpecifier ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  XmString ;
struct TYPE_9__ {int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ XmListCallbackStruct ;
typedef  scalar_t__ Widget ;
struct TYPE_10__ {char** sel; char* font_name; int num; int /*<<< orphan*/  name; int /*<<< orphan*/  sample; } ;
typedef  TYPE_2__ SharedFontSelData ;
typedef  int /*<<< orphan*/  Boolean ;
typedef  int /*<<< orphan*/  Arg ;

/* Variables and functions */
 size_t ENCODING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  False ; 
 size_t NAME ; 
 size_t SIZE ; 
 size_t STYLE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  VIM_ERROR ; 
 int /*<<< orphan*/  XmListDeselectItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNlabelString ; 
 int /*<<< orphan*/  XmSTRING_DEFAULT_CHARSET ; 
 int /*<<< orphan*/  XmStringCreateLocalized (char*) ; 
 int /*<<< orphan*/  XmStringFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmStringGetLtoR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  XmTextSetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XtFree (char*) ; 
 void* XtNewString (char*) ; 
 int /*<<< orphan*/  XtSetArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtSetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  apply_fontlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_sample (TYPE_2__*) ; 
 int /*<<< orphan*/  do_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_lists (int,TYPE_2__*) ; 
 char* fn (TYPE_2__*,int) ; 
 scalar_t__ match (TYPE_2__*,size_t,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* wild ; 

__attribute__((used)) static Boolean
do_choice(Widget w,
	SharedFontSelData *data,
	XmListCallbackStruct *call_data,
	enum ListSpecifier which)
{
    char *sel;

    XmStringGetLtoR(call_data->item, XmSTRING_DEFAULT_CHARSET, &sel);

    if (!data->sel[which])
	data->sel[which] = XtNewString(sel);
    else
    {
	if (!strcmp(data->sel[which], sel))
	{
	    /* unselecting current selection */
	    XtFree(data->sel[which]);
	    data->sel[which] = NULL;
	    if (w)
		XmListDeselectItem(w, call_data->item);
	}
	else
	{
	    XtFree(data->sel[which]);
	    data->sel[which] = XtNewString(sel);
	}
    }
    XtFree(sel);

    fill_lists(which, data);

    /* If there is a font selection, we display it. */
    if (data->sel[ENCODING]
	    && data->sel[NAME]
	    && data->sel[STYLE]
	    && data->sel[SIZE]
	    && strcmp(data->sel[ENCODING], wild)
	    && strcmp(data->sel[NAME], wild)
	    && strcmp(data->sel[STYLE], wild)
	    && strcmp(data->sel[SIZE], wild))
    {
	int i;

	if (data->font_name)
	    XtFree(data->font_name);
	data->font_name = NULL;

	for (i = 0; i < data->num; i++)
	{
	    if (match(data, ENCODING, i)
		    && match(data, NAME, i)
		    && match(data, STYLE, i)
		    && match(data, SIZE, i))
	    {
		data->font_name = XtNewString(fn(data, i));
		break;
	    }
	}

	if (data->font_name)
	{
	    XmTextSetString(data->name, data->font_name);
	    display_sample(data);
	}
	else
	    do_dialog(VIM_ERROR,
		    (char_u *)_("Error"),
		    (char_u *)_("Invalid font specification"),
		    (char_u *)_("&Dismiss"), 1, NULL, FALSE);

	return True;
    }
    else
    {
	int	    n;
	XmString    str;
	Arg	    args[4];
	char	    *nomatch_msg = _("no specific match");

	n = 0;
	str = XmStringCreateLocalized(nomatch_msg);
	XtSetArg(args[n], XmNlabelString, str); ++n;
	XtSetValues(data->sample, args, n);
	apply_fontlist(data->sample);
	XmTextSetString(data->name, nomatch_msg);
	XmStringFree(str);

	return False;
    }
}