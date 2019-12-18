#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ lnum; int col; } ;
typedef  TYPE_1__ pos_T ;
typedef  scalar_t__ colnr_T ;
typedef  char char_u ;
struct TYPE_13__ {scalar_t__ lnum; int col; } ;
struct TYPE_12__ {int w_p_list; TYPE_1__ w_cursor; } ;
struct TYPE_11__ {scalar_t__ b_p_ts; scalar_t__ b_p_sts; int /*<<< orphan*/  b_p_et; } ;

/* Variables and functions */
 char ABBR_OFF ; 
 int /*<<< orphan*/  AppendToRedobuff (char*) ; 
 int /*<<< orphan*/  CPO_LISTWM ; 
 scalar_t__ FAIL ; 
 int FALSE ; 
 TYPE_9__ Insstart ; 
 scalar_t__ Insstart_blank_vcol ; 
 scalar_t__ MAXCOL ; 
 int /*<<< orphan*/  NUL ; 
 int REPLACE_FLAG ; 
 int /*<<< orphan*/  STRMOVE (char*,char*) ; 
 int State ; 
 char TAB ; 
 int TRUE ; 
 int VREPLACE_FLAG ; 
 int /*<<< orphan*/  backspace_until_column (int) ; 
 int can_cindent ; 
 int can_si ; 
 int can_si_back ; 
 TYPE_2__* curbuf ; 
 TYPE_4__* curwin ; 
 int did_ai ; 
 int did_si ; 
 scalar_t__ echeck_abbr (char) ; 
 int get_nolist_virtcol () ; 
 scalar_t__ get_sts_value () ; 
 scalar_t__ get_sw_value (TYPE_2__*) ; 
 int /*<<< orphan*/  getvcol (TYPE_4__*,TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inindent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ins_bytes_len (char*,int) ; 
 int /*<<< orphan*/  ins_char (char) ; 
 int /*<<< orphan*/  ins_str (char*) ; 
 int lbr_chartabsize (char*,scalar_t__) ; 
 int /*<<< orphan*/  ml_get_curline () ; 
 char* ml_get_cursor () ; 
 scalar_t__ netbeans_active () ; 
 int /*<<< orphan*/  netbeans_inserted (TYPE_2__*,scalar_t__,int,char*,int) ; 
 int /*<<< orphan*/  netbeans_removed (TYPE_2__*,scalar_t__,int,long) ; 
 int /*<<< orphan*/  p_cpo ; 
 scalar_t__ p_sta ; 
 int /*<<< orphan*/  replace_join (int) ; 
 int /*<<< orphan*/  replace_push (int /*<<< orphan*/ ) ; 
 scalar_t__ stop_arrow () ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 scalar_t__ vim_iswhite (char) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* vim_strsave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ins_tab()
{
    int		ind;
    int		i;
    int		temp;

    if (Insstart_blank_vcol == MAXCOL && curwin->w_cursor.lnum == Insstart.lnum)
	Insstart_blank_vcol = get_nolist_virtcol();
    if (echeck_abbr(TAB + ABBR_OFF))
	return FALSE;

    ind = inindent(0);
#ifdef FEAT_CINDENT
    if (ind)
	can_cindent = FALSE;
#endif

    /*
     * When nothing special, insert TAB like a normal character
     */
    if (!curbuf->b_p_et
	    && !(p_sta && ind && curbuf->b_p_ts != get_sw_value(curbuf))
	    && get_sts_value() == 0)
	return TRUE;

    if (stop_arrow() == FAIL)
	return TRUE;

    did_ai = FALSE;
#ifdef FEAT_SMARTINDENT
    did_si = FALSE;
    can_si = FALSE;
    can_si_back = FALSE;
#endif
    AppendToRedobuff((char_u *)"\t");

    if (p_sta && ind)		/* insert tab in indent, use 'shiftwidth' */
	temp = (int)get_sw_value(curbuf);
    else if (curbuf->b_p_sts != 0) /* use 'softtabstop' when set */
	temp = (int)get_sts_value();
    else			/* otherwise use 'tabstop' */
	temp = (int)curbuf->b_p_ts;
    temp -= get_nolist_virtcol() % temp;

    /*
     * Insert the first space with ins_char().	It will delete one char in
     * replace mode.  Insert the rest with ins_str(); it will not delete any
     * chars.  For VREPLACE mode, we use ins_char() for all characters.
     */
    ins_char(' ');
    while (--temp > 0)
    {
#ifdef FEAT_VREPLACE
	if (State & VREPLACE_FLAG)
	    ins_char(' ');
	else
#endif
	{
	    ins_str((char_u *)" ");
	    if (State & REPLACE_FLAG)	    /* no char replaced */
		replace_push(NUL);
	}
    }

    /*
     * When 'expandtab' not set: Replace spaces by TABs where possible.
     */
    if (!curbuf->b_p_et && (get_sts_value() || (p_sta && ind)))
    {
	char_u		*ptr;
#ifdef FEAT_VREPLACE
	char_u		*saved_line = NULL;	/* init for GCC */
	pos_T		pos;
#endif
	pos_T		fpos;
	pos_T		*cursor;
	colnr_T		want_vcol, vcol;
	int		change_col = -1;
	int		save_list = curwin->w_p_list;

	/*
	 * Get the current line.  For VREPLACE mode, don't make real changes
	 * yet, just work on a copy of the line.
	 */
#ifdef FEAT_VREPLACE
	if (State & VREPLACE_FLAG)
	{
	    pos = curwin->w_cursor;
	    cursor = &pos;
	    saved_line = vim_strsave(ml_get_curline());
	    if (saved_line == NULL)
		return FALSE;
	    ptr = saved_line + pos.col;
	}
	else
#endif
	{
	    ptr = ml_get_cursor();
	    cursor = &curwin->w_cursor;
	}

	/* When 'L' is not in 'cpoptions' a tab always takes up 'ts' spaces. */
	if (vim_strchr(p_cpo, CPO_LISTWM) == NULL)
	    curwin->w_p_list = FALSE;

	/* Find first white before the cursor */
	fpos = curwin->w_cursor;
	while (fpos.col > 0 && vim_iswhite(ptr[-1]))
	{
	    --fpos.col;
	    --ptr;
	}

	/* In Replace mode, don't change characters before the insert point. */
	if ((State & REPLACE_FLAG)
		&& fpos.lnum == Insstart.lnum
		&& fpos.col < Insstart.col)
	{
	    ptr += Insstart.col - fpos.col;
	    fpos.col = Insstart.col;
	}

	/* compute virtual column numbers of first white and cursor */
	getvcol(curwin, &fpos, &vcol, NULL, NULL);
	getvcol(curwin, cursor, &want_vcol, NULL, NULL);

	/* Use as many TABs as possible.  Beware of 'showbreak' and
	 * 'linebreak' adding extra virtual columns. */
	while (vim_iswhite(*ptr))
	{
	    i = lbr_chartabsize((char_u *)"\t", vcol);
	    if (vcol + i > want_vcol)
		break;
	    if (*ptr != TAB)
	    {
		*ptr = TAB;
		if (change_col < 0)
		{
		    change_col = fpos.col;  /* Column of first change */
		    /* May have to adjust Insstart */
		    if (fpos.lnum == Insstart.lnum && fpos.col < Insstart.col)
			Insstart.col = fpos.col;
		}
	    }
	    ++fpos.col;
	    ++ptr;
	    vcol += i;
	}

	if (change_col >= 0)
	{
	    int repl_off = 0;

	    /* Skip over the spaces we need. */
	    while (vcol < want_vcol && *ptr == ' ')
	    {
		vcol += lbr_chartabsize(ptr, vcol);
		++ptr;
		++repl_off;
	    }
	    if (vcol > want_vcol)
	    {
		/* Must have a char with 'showbreak' just before it. */
		--ptr;
		--repl_off;
	    }
	    fpos.col += repl_off;

	    /* Delete following spaces. */
	    i = cursor->col - fpos.col;
	    if (i > 0)
	    {
		STRMOVE(ptr, ptr + i);
		/* correct replace stack. */
		if ((State & REPLACE_FLAG)
#ifdef FEAT_VREPLACE
			&& !(State & VREPLACE_FLAG)
#endif
			)
		    for (temp = i; --temp >= 0; )
			replace_join(repl_off);
	    }
#ifdef FEAT_NETBEANS_INTG
	    if (netbeans_active())
	    {
		netbeans_removed(curbuf, fpos.lnum, cursor->col, (long)(i + 1));
		netbeans_inserted(curbuf, fpos.lnum, cursor->col,
							   (char_u *)"\t", 1);
	    }
#endif
	    cursor->col -= i;

#ifdef FEAT_VREPLACE
	    /*
	     * In VREPLACE mode, we haven't changed anything yet.  Do it now by
	     * backspacing over the changed spacing and then inserting the new
	     * spacing.
	     */
	    if (State & VREPLACE_FLAG)
	    {
		/* Backspace from real cursor to change_col */
		backspace_until_column(change_col);

		/* Insert each char in saved_line from changed_col to
		 * ptr-cursor */
		ins_bytes_len(saved_line + change_col,
						    cursor->col - change_col);
	    }
#endif
	}

#ifdef FEAT_VREPLACE
	if (State & VREPLACE_FLAG)
	    vim_free(saved_line);
#endif
	curwin->w_p_list = save_list;
    }

    return FALSE;
}