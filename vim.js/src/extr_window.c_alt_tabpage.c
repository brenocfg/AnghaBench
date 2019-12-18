#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* tp_next; } ;
typedef  TYPE_1__ tabpage_T ;

/* Variables and functions */
 TYPE_1__* curtab ; 
 TYPE_1__* first_tabpage ; 

__attribute__((used)) static tabpage_T *
alt_tabpage()
{
    tabpage_T	*tp;

    /* Use the next tab page if possible. */
    if (curtab->tp_next != NULL)
	return curtab->tp_next;

    /* Find the last but one tab page. */
    for (tp = first_tabpage; tp->tp_next != curtab; tp = tp->tp_next)
	;
    return tp;
}