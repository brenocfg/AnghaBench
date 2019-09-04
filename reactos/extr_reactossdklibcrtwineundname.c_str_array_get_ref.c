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
struct array {unsigned int start; unsigned int max; char** elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct array*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,struct array*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert (struct array*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static char* str_array_get_ref(struct array* cref, unsigned idx)
{
    assert(cref);
    if (cref->start + idx >= cref->max)
    {
        WARN("Out of bounds: %p %d + %d >= %d\n", 
              cref, cref->start, idx, cref->max);
        return NULL;
    }
    TRACE("Returning %p[%d] => %s\n", 
          cref, idx, debugstr_a(cref->elts[cref->start + idx]));
    return cref->elts[cref->start + idx];
}