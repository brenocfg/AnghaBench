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
typedef  int long_u ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_FREE ; 
 int /*<<< orphan*/  OPT_LOCAL ; 
 int P_WAS_SET ; 
 int Rows ; 
 int /*<<< orphan*/  SHAPE_CURSOR ; 
 int /*<<< orphan*/  SHAPE_MOUSE ; 
 int /*<<< orphan*/  comp_col () ; 
 int findoption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  option_was_set (int /*<<< orphan*/ *) ; 
 TYPE_1__* options ; 
 int /*<<< orphan*/  p_cp ; 
 int p_window ; 
 int /*<<< orphan*/  parse_printoptions () ; 
 int /*<<< orphan*/  parse_shape_opt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_number_default (char*,int) ; 
 int /*<<< orphan*/  set_option_default (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_string_option_direct (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* term_bg_default () ; 

void
set_init_2()
{
    int		idx;

    /*
     * 'scroll' defaults to half the window height. Note that this default is
     * wrong when the window height changes.
     */
    set_number_default("scroll", (long)((long_u)Rows >> 1));
    idx = findoption((char_u *)"scroll");
    if (idx >= 0 && !(options[idx].flags & P_WAS_SET))
	set_option_default(idx, OPT_LOCAL, p_cp);
    comp_col();

    /*
     * 'window' is only for backwards compatibility with Vi.
     * Default is Rows - 1.
     */
    if (!option_was_set((char_u *)"window"))
	p_window = Rows - 1;
    set_number_default("window", Rows - 1);

    /* For DOS console the default is always black. */
#if !((defined(MSDOS) || defined(OS2) || defined(WIN3264)) && !defined(FEAT_GUI))
    /*
     * If 'background' wasn't set by the user, try guessing the value,
     * depending on the terminal name.  Only need to check for terminals
     * with a dark background, that can handle color.
     */
    idx = findoption((char_u *)"bg");
    if (idx >= 0 && !(options[idx].flags & P_WAS_SET)
						 && *term_bg_default() == 'd')
    {
	set_string_option_direct(NULL, idx, (char_u *)"dark", OPT_FREE, 0);
	/* don't mark it as set, when starting the GUI it may be
	 * changed again */
	options[idx].flags &= ~P_WAS_SET;
    }
#endif

#ifdef CURSOR_SHAPE
    parse_shape_opt(SHAPE_CURSOR); /* set cursor shapes from 'guicursor' */
#endif
#ifdef FEAT_MOUSESHAPE
    parse_shape_opt(SHAPE_MOUSE);  /* set mouse shapes from 'mouseshape' */
#endif
#ifdef FEAT_PRINTER
    (void)parse_printoptions();	    /* parse 'printoptions' default value */
#endif
}