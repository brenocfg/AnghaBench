#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int char_u ;
struct TYPE_6__ {scalar_t__ w_p_rl; } ;
struct TYPE_5__ {int* pum_text; int* pum_kind; int* pum_extra; } ;

/* Variables and functions */
 size_t HLF_PNI ; 
 size_t HLF_PSB ; 
 size_t HLF_PSI ; 
 size_t HLF_PST ; 
 int NUL ; 
 scalar_t__ STRLEN (int*) ; 
 int TAB ; 
 int W_WIDTH (TYPE_2__*) ; 
 int W_WINCOL (TYPE_2__*) ; 
 TYPE_2__* curwin ; 
 scalar_t__ has_mbyte ; 
 int* highlight_attr ; 
 int mb_ptr2cells (int*) ; 
 int /*<<< orphan*/  mb_ptr_adv (int*) ; 
 int ptr2cells (int*) ; 
 TYPE_1__* pum_array ; 
 int pum_base_width ; 
 int pum_col ; 
 int pum_first ; 
 int pum_height ; 
 int pum_kind_width ; 
 int pum_row ; 
 scalar_t__ pum_scrollbar ; 
 int pum_selected ; 
 int pum_size ; 
 int pum_width ; 
 int* reverse_text (int*) ; 
 int /*<<< orphan*/  screen_fill (int,int,int,int,char,char,int) ; 
 int /*<<< orphan*/  screen_putchar (char,int,int,int) ; 
 int /*<<< orphan*/  screen_puts_len (int*,int,int,int,int) ; 
 int stub1 (int*) ; 
 int* transstr (int*) ; 
 int /*<<< orphan*/  vim_free (int*) ; 
 int vim_strsize (int*) ; 

void
pum_redraw()
{
    int		row = pum_row;
    int		col;
    int		attr_norm = highlight_attr[HLF_PNI];
    int		attr_select = highlight_attr[HLF_PSI];
    int		attr_scroll = highlight_attr[HLF_PSB];
    int		attr_thumb = highlight_attr[HLF_PST];
    int		attr;
    int		i;
    int		idx;
    char_u	*s;
    char_u	*p = NULL;
    int		totwidth, width, w;
    int		thumb_pos = 0;
    int		thumb_heigth = 1;
    int		round;
    int		n;

    /* Never display more than we have */
    if (pum_first > pum_size - pum_height)
	pum_first = pum_size - pum_height;

    if (pum_scrollbar)
    {
	thumb_heigth = pum_height * pum_height / pum_size;
	if (thumb_heigth == 0)
	    thumb_heigth = 1;
	thumb_pos = (pum_first * (pum_height - thumb_heigth)
			    + (pum_size - pum_height) / 2)
						    / (pum_size - pum_height);
    }

    for (i = 0; i < pum_height; ++i)
    {
	idx = i + pum_first;
	attr = (idx == pum_selected) ? attr_select : attr_norm;

	/* prepend a space if there is room */
#ifdef FEAT_RIGHTLEFT
	if (curwin->w_p_rl)
	{
	    if (pum_col < W_WINCOL(curwin) + W_WIDTH(curwin) - 1)
		screen_putchar(' ', row, pum_col + 1, attr);
	}
	else
#endif
	    if (pum_col > 0)
		screen_putchar(' ', row, pum_col - 1, attr);

	/* Display each entry, use two spaces for a Tab.
	 * Do this 3 times: For the main text, kind and extra info */
	col = pum_col;
	totwidth = 0;
	for (round = 1; round <= 3; ++round)
	{
	    width = 0;
	    s = NULL;
	    switch (round)
	    {
		case 1: p = pum_array[idx].pum_text; break;
		case 2: p = pum_array[idx].pum_kind; break;
		case 3: p = pum_array[idx].pum_extra; break;
	    }
	    if (p != NULL)
		for ( ; ; mb_ptr_adv(p))
		{
		    if (s == NULL)
			s = p;
		    w = ptr2cells(p);
		    if (*p == NUL || *p == TAB || totwidth + w > pum_width)
		    {
			/* Display the text that fits or comes before a Tab.
			 * First convert it to printable characters. */
			char_u	*st;
			int	saved = *p;

			*p = NUL;
			st = transstr(s);
			*p = saved;
#ifdef FEAT_RIGHTLEFT
			if (curwin->w_p_rl)
			{
			    if (st != NULL)
			    {
				char_u	*rt = reverse_text(st);

				if (rt != NULL)
				{
				    char_u	*rt_start = rt;
				    int		size;

				    size = vim_strsize(rt);
				    if (size > pum_width)
				    {
					do
					{
					    size -= has_mbyte
						    ? (*mb_ptr2cells)(rt) : 1;
					    mb_ptr_adv(rt);
					} while (size > pum_width);

					if (size < pum_width)
					{
					    /* Most left character requires
					     * 2-cells but only 1 cell is
					     * available on screen.  Put a
					     * '<' on the left of the pum
					     * item */
					    *(--rt) = '<';
					    size++;
					}
				    }
				    screen_puts_len(rt, (int)STRLEN(rt),
						   row, col - size + 1, attr);
				    vim_free(rt_start);
				}
				vim_free(st);
			    }
			    col -= width;
			}
			else
#endif
			{
			    if (st != NULL)
			    {
				screen_puts_len(st, (int)STRLEN(st), row, col,
									attr);
				vim_free(st);
			    }
			    col += width;
			}

			if (*p != TAB)
			    break;

			/* Display two spaces for a Tab. */
#ifdef FEAT_RIGHTLEFT
			if (curwin->w_p_rl)
			{
			    screen_puts_len((char_u *)"  ", 2, row, col - 1,
									attr);
			    col -= 2;
			}
			else
#endif
			{
			    screen_puts_len((char_u *)"  ", 2, row, col, attr);
			    col += 2;
			}
			totwidth += 2;
			s = NULL;	    /* start text at next char */
			width = 0;
		    }
		    else
			width += w;
		}

	    if (round > 1)
		n = pum_kind_width + 1;
	    else
		n = 1;

	    /* Stop when there is nothing more to display. */
	    if (round == 3
		    || (round == 2 && pum_array[idx].pum_extra == NULL)
		    || (round == 1 && pum_array[idx].pum_kind == NULL
					  && pum_array[idx].pum_extra == NULL)
		    || pum_base_width + n >= pum_width)
		break;
#ifdef FEAT_RIGHTLEFT
	    if (curwin->w_p_rl)
	    {
		screen_fill(row, row + 1, pum_col - pum_base_width - n + 1,
						    col + 1, ' ', ' ', attr);
		col = pum_col - pum_base_width - n + 1;
	    }
	    else
#endif
	    {
		screen_fill(row, row + 1, col, pum_col + pum_base_width + n,
							      ' ', ' ', attr);
		col = pum_col + pum_base_width + n;
	    }
	    totwidth = pum_base_width + n;
	}

#ifdef FEAT_RIGHTLEFT
	if (curwin->w_p_rl)
	    screen_fill(row, row + 1, pum_col - pum_width + 1, col + 1, ' ',
								    ' ', attr);
	else
#endif
	    screen_fill(row, row + 1, col, pum_col + pum_width, ' ', ' ',
									attr);
	if (pum_scrollbar > 0)
	{
#ifdef FEAT_RIGHTLEFT
	    if (curwin->w_p_rl)
		screen_putchar(' ', row, pum_col - pum_width,
			i >= thumb_pos && i < thumb_pos + thumb_heigth
						  ? attr_thumb : attr_scroll);
	    else
#endif
		screen_putchar(' ', row, pum_col + pum_width,
			i >= thumb_pos && i < thumb_pos + thumb_heigth
						  ? attr_thumb : attr_scroll);
	}

	++row;
    }
}