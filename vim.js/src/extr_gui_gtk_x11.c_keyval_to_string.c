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
typedef  int guint32 ;
typedef  int char_u ;

/* Variables and functions */
 int BS ; 
 int CAR ; 
 int DEL ; 
 int ESC ; 
#define  GDK_3270_Enter 135 
 unsigned int GDK_CONTROL_MASK ; 
#define  GDK_Escape 134 
#define  GDK_ISO_Enter 133 
#define  GDK_ISO_Left_Tab 132 
#define  GDK_KP_Tab 131 
#define  GDK_Linefeed 130 
#define  GDK_Return 129 
#define  GDK_Tab 128 
 int NL ; 
 int NUL ; 
 int TAB ; 
 int gdk_keyval_to_unicode (unsigned int) ; 
 int utf_char2bytes (int,int*) ; 

__attribute__((used)) static int
keyval_to_string(unsigned int keyval, unsigned int state, char_u *string)
{
    int	    len;
    guint32 uc;

    uc = gdk_keyval_to_unicode(keyval);
    if (uc != 0)
    {
	/* Check for CTRL-foo */
	if ((state & GDK_CONTROL_MASK) && uc >= 0x20 && uc < 0x80)
	{
	    /* These mappings look arbitrary at the first glance, but in fact
	     * resemble quite exactly the behaviour of the GTK+ 1.2 GUI on my
	     * machine.  The only difference is BS vs. DEL for CTRL-8 (makes
	     * more sense and is consistent with usual terminal behaviour). */
	    if (uc >= '@')
		string[0] = uc & 0x1F;
	    else if (uc == '2')
		string[0] = NUL;
	    else if (uc >= '3' && uc <= '7')
		string[0] = uc ^ 0x28;
	    else if (uc == '8')
		string[0] = BS;
	    else if (uc == '?')
		string[0] = DEL;
	    else
		string[0] = uc;
	    len = 1;
	}
	else
	{
	    /* Translate a normal key to UTF-8.  This doesn't work for dead
	     * keys of course, you _have_ to use an input method for that. */
	    len = utf_char2bytes((int)uc, string);
	}
    }
    else
    {
	/* Translate keys which are represented by ASCII control codes in Vim.
	 * There are only a few of those; most control keys are translated to
	 * special terminal-like control sequences. */
	len = 1;
	switch (keyval)
	{
	    case GDK_Tab: case GDK_KP_Tab: case GDK_ISO_Left_Tab:
		string[0] = TAB;
		break;
	    case GDK_Linefeed:
		string[0] = NL;
		break;
	    case GDK_Return: case GDK_ISO_Enter: case GDK_3270_Enter:
		string[0] = CAR;
		break;
	    case GDK_Escape:
		string[0] = ESC;
		break;
	    default:
		len = 0;
		break;
	}
    }
    string[len] = NUL;

    return len;
}