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
struct TYPE_4__ {int active; int /*<<< orphan*/  n_allocated; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ CacheMem ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static int cachemem_maintain(CacheMem *mem, unsigned size) {
        assert(mem);

        if (!GREEDY_REALLOC(mem->ptr, mem->n_allocated, size)) {
                if (size > 0)
                        return -ENOMEM;
        }

        if (!mem->active) {
                mem->active = true;
                return true;
        }

        return false;
}