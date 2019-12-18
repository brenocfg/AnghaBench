#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct TYPE_8__ {TYPE_2__ term; } ;
struct TYPE_10__ {TYPE_1__ ae_u; } ;
typedef  TYPE_3__ attrentry_T ;
struct TYPE_11__ {int ga_len; scalar_t__ ga_data; } ;

/* Variables and functions */
 TYPE_4__ cterm_attr_table ; 
 int /*<<< orphan*/  ga_clear (TYPE_4__*) ; 
 TYPE_4__ gui_attr_table ; 
 TYPE_4__ term_attr_table ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ ) ; 

void
clear_hl_tables()
{
    int		i;
    attrentry_T	*taep;

#ifdef FEAT_GUI
    ga_clear(&gui_attr_table);
#endif
    for (i = 0; i < term_attr_table.ga_len; ++i)
    {
	taep = &(((attrentry_T *)term_attr_table.ga_data)[i]);
	vim_free(taep->ae_u.term.start);
	vim_free(taep->ae_u.term.stop);
    }
    ga_clear(&term_attr_table);
    ga_clear(&cterm_attr_table);
}