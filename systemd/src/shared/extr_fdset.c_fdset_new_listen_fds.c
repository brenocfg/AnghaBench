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
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * fdset_new () ; 
 int fdset_put (int /*<<< orphan*/ *,int) ; 
 int sd_listen_fds (int) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

int fdset_new_listen_fds(FDSet **_s, bool unset) {
        int n, fd, r;
        FDSet *s;

        assert(_s);

        /* Creates an fdset and fills in all passed file descriptors */

        s = fdset_new();
        if (!s) {
                r = -ENOMEM;
                goto fail;
        }

        n = sd_listen_fds(unset);
        for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START + n; fd ++) {
                r = fdset_put(s, fd);
                if (r < 0)
                        goto fail;
        }

        *_s = s;
        return 0;

fail:
        if (s)
                set_free(MAKE_SET(s));

        return r;
}