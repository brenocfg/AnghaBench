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
struct TYPE_2__ {int /*<<< orphan*/  starting; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_nogvim ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  mch_errmsg (char*) ; 
 int /*<<< orphan*/  mch_exit (int) ; 

__attribute__((used)) static void
main_start_gui()
{
#ifdef FEAT_GUI
    gui.starting = TRUE;	/* start GUI a bit later */
#else
    mch_errmsg(_(e_nogvim));
    mch_errmsg("\n");
    mch_exit(2);
#endif
}