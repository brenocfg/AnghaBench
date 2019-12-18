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
typedef  size_t uint32_t ;
struct array {size_t size; size_t nalloc; scalar_t__ nelem; int /*<<< orphan*/ * elem; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/ * nc_alloc (size_t) ; 

rstatus_t
array_init(struct array *a, uint32_t n, size_t size)
{
    ASSERT(n != 0 && size != 0);

    a->elem = nc_alloc(n * size);
    if (a->elem == NULL) {
        return NC_ENOMEM;
    }

    a->nelem = 0;
    a->size = size;
    a->nalloc = n;

    return NC_OK;
}