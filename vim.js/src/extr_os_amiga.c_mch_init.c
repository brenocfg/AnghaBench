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
struct IntuitionBase {int dummy; } ;
typedef  int /*<<< orphan*/  UBYTE ;
typedef  scalar_t__ BPTR ;

/* Variables and functions */
 int Columns ; 
 scalar_t__ Enable_Abort ; 
 scalar_t__ Input () ; 
 struct IntuitionBase* IntuitionBase ; 
 int /*<<< orphan*/  IsInteractive (scalar_t__) ; 
 scalar_t__ OpenLibrary (int /*<<< orphan*/ *,long) ; 
 scalar_t__ Output () ; 
 int Rows ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  mch_errmsg (char*) ; 
 int /*<<< orphan*/  mch_exit (int) ; 
 int /*<<< orphan*/  out_flush () ; 
 scalar_t__ raw_in ; 
 scalar_t__ raw_out ; 
 int /*<<< orphan*/ * wb_window ; 

void
mch_init()
{
    static char	    intlibname[] = "intuition.library";

#ifdef AZTEC_C
    Enable_Abort = 0;		/* disallow vim to be aborted */
#endif
    Columns = 80;
    Rows = 24;

    /*
     * Set input and output channels, unless we have opened our own window
     */
    if (raw_in == (BPTR)NULL)
    {
	raw_in = Input();
	raw_out = Output();
	/*
	 * If Input() is not interactive, then Output() will be (because of
	 * check in mch_check_win()).  Used for "Vim -".
	 * Also check the other way around, for "Vim -h | more".
	 */
	if (!IsInteractive(raw_in))
	    raw_in = raw_out;
	else if (!IsInteractive(raw_out))
	    raw_out = raw_in;
    }

    out_flush();

    wb_window = NULL;
#ifndef __amigaos4__
    if ((IntuitionBase = (struct IntuitionBase *)
				OpenLibrary((UBYTE *)intlibname, 0L)) == NULL)
    {
	mch_errmsg(_("cannot open "));
	mch_errmsg(intlibname);
	mch_errmsg("!?\n");
	mch_exit(3);
    }
#endif
}