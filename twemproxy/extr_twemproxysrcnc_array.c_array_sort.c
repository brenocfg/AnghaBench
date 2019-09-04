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
struct array {scalar_t__ nelem; int /*<<< orphan*/  size; int /*<<< orphan*/  elem; } ;
typedef  int /*<<< orphan*/  array_compare_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
array_sort(struct array *a, array_compare_t compare)
{
    ASSERT(a->nelem != 0);

    qsort(a->elem, a->nelem, a->size, compare);
}