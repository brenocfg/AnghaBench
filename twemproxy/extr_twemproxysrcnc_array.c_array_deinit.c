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
struct array {scalar_t__ nelem; int /*<<< orphan*/ * elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  nc_free (int /*<<< orphan*/ *) ; 

void
array_deinit(struct array *a)
{
    ASSERT(a->nelem == 0);

    if (a->elem != NULL) {
        nc_free(a->elem);
    }
}