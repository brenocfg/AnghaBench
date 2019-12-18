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
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MAKE_SET (int /*<<< orphan*/ *) ; 
 int PTR_TO_FD (void*) ; 
 void* set_steal_first (int /*<<< orphan*/ ) ; 

int fdset_steal_first(FDSet *fds) {
        void *p;

        p = set_steal_first(MAKE_SET(fds));
        if (!p)
                return -ENOENT;

        return PTR_TO_FD(p);
}