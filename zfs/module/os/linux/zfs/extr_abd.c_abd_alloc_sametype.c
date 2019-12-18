#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_8__ {int abd_flags; } ;
typedef  TYPE_1__ abd_t ;

/* Variables and functions */
 int ABD_FLAG_META ; 
 TYPE_1__* abd_alloc (size_t,int) ; 
 TYPE_1__* abd_alloc_linear (size_t,int) ; 
 scalar_t__ abd_is_linear (TYPE_1__*) ; 
 int /*<<< orphan*/  abd_is_linear_page (TYPE_1__*) ; 

abd_t *
abd_alloc_sametype(abd_t *sabd, size_t size)
{
	boolean_t is_metadata = (sabd->abd_flags & ABD_FLAG_META) != 0;
	if (abd_is_linear(sabd) &&
	    !abd_is_linear_page(sabd)) {
		return (abd_alloc_linear(size, is_metadata));
	} else {
		return (abd_alloc(size, is_metadata));
	}
}