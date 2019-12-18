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
typedef  scalar_t__ long_i ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_4__ {scalar_t__ in_use; scalar_t__ starting; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ ** def_val; } ;

/* Variables and functions */
 int P_WAS_SET ; 
 long TRUE ; 
 size_t VI_DEFAULT ; 
 int findoption (int /*<<< orphan*/ *) ; 
 TYPE_2__ gui ; 
 long mch_can_restore_icon () ; 
 long mch_can_restore_title () ; 
 TYPE_1__* options ; 
 long p_icon ; 
 long p_title ; 

void
set_title_defaults()
{
    int	    idx1;
    long    val;

    /*
     * If GUI is (going to be) used, we can always set the window title and
     * icon name.  Saves a bit of time, because the X11 display server does
     * not need to be contacted.
     */
    idx1 = findoption((char_u *)"title");
    if (idx1 >= 0 && !(options[idx1].flags & P_WAS_SET))
    {
#ifdef FEAT_GUI
	if (gui.starting || gui.in_use)
	    val = TRUE;
	else
#endif
	    val = mch_can_restore_title();
	options[idx1].def_val[VI_DEFAULT] = (char_u *)(long_i)val;
	p_title = val;
    }
    idx1 = findoption((char_u *)"icon");
    if (idx1 >= 0 && !(options[idx1].flags & P_WAS_SET))
    {
#ifdef FEAT_GUI
	if (gui.starting || gui.in_use)
	    val = TRUE;
	else
#endif
	    val = mch_can_restore_icon();
	options[idx1].def_val[VI_DEFAULT] = (char_u *)(long_i)val;
	p_icon = val;
    }
}