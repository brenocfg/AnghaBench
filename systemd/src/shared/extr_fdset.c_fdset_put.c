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
 int /*<<< orphan*/  FD_TO_PTR (int) ; 
 int /*<<< orphan*/  MAKE_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fdset_put(FDSet *s, int fd) {
        assert(s);
        assert(fd >= 0);

        return set_put(MAKE_SET(s), FD_TO_PTR(fd));
}