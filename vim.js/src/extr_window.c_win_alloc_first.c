#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tp_topframe; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int OK ; 
 TYPE_1__* alloc_tabpage () ; 
 TYPE_1__* curtab ; 
 TYPE_1__* first_tabpage ; 
 int /*<<< orphan*/  topframe ; 
 scalar_t__ win_alloc_firstwin (int /*<<< orphan*/ *) ; 

int
win_alloc_first()
{
    if (win_alloc_firstwin(NULL) == FAIL)
	return FAIL;

#ifdef FEAT_WINDOWS
    first_tabpage = alloc_tabpage();
    if (first_tabpage == NULL)
	return FAIL;
    first_tabpage->tp_topframe = topframe;
    curtab = first_tabpage;
#endif

    return OK;
}