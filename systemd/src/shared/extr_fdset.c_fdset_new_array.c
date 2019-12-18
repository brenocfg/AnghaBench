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
 int ENOMEM ; 
 int /*<<< orphan*/  MAKE_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * fdset_new () ; 
 int fdset_put (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

int fdset_new_array(FDSet **ret, const int *fds, size_t n_fds) {
        size_t i;
        FDSet *s;
        int r;

        assert(ret);

        s = fdset_new();
        if (!s)
                return -ENOMEM;

        for (i = 0; i < n_fds; i++) {

                r = fdset_put(s, fds[i]);
                if (r < 0) {
                        set_free(MAKE_SET(s));
                        return r;
                }
        }

        *ret = s;
        return 0;
}