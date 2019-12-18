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
struct array {scalar_t__ nelem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* array_get (struct array*,scalar_t__) ; 

void *
array_top(struct array *a)
{
    ASSERT(a->nelem != 0);

    return array_get(a, a->nelem - 1);
}