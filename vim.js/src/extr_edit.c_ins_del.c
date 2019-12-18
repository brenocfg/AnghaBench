#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AppendCharToRedobuff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BS_EOL ; 
 scalar_t__ FAIL ; 
 void* FALSE ; 
 int /*<<< orphan*/  K_DEL ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  can_bs (int /*<<< orphan*/ ) ; 
 void* can_si ; 
 void* can_si_back ; 
 TYPE_2__* curwin ; 
 scalar_t__ del_char (void*) ; 
 void* did_ai ; 
 void* did_si ; 
 scalar_t__ do_join (int,void*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ gchar_cursor () ; 
 scalar_t__ stop_arrow () ; 
 int /*<<< orphan*/  vim_beep () ; 

__attribute__((used)) static void
ins_del()
{
    int	    temp;

    if (stop_arrow() == FAIL)
	return;
    if (gchar_cursor() == NUL)		/* delete newline */
    {
	temp = curwin->w_cursor.col;
	if (!can_bs(BS_EOL)		/* only if "eol" included */
		|| do_join(2, FALSE, TRUE, FALSE) == FAIL)
	    vim_beep();
	else
	    curwin->w_cursor.col = temp;
    }
    else if (del_char(FALSE) == FAIL)	/* delete char under cursor */
	vim_beep();
    did_ai = FALSE;
#ifdef FEAT_SMARTINDENT
    did_si = FALSE;
    can_si = FALSE;
    can_si_back = FALSE;
#endif
    AppendCharToRedobuff(K_DEL);
}