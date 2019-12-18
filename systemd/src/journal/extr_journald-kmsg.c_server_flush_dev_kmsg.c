#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dev_kmsg_fd; int /*<<< orphan*/  dev_kmsg_readable; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int server_read_dev_kmsg (TYPE_1__*) ; 

int server_flush_dev_kmsg(Server *s) {
        int r;

        assert(s);

        if (s->dev_kmsg_fd < 0)
                return 0;

        if (!s->dev_kmsg_readable)
                return 0;

        log_debug("Flushing /dev/kmsg...");

        for (;;) {
                r = server_read_dev_kmsg(s);
                if (r < 0)
                        return r;

                if (r == 0)
                        break;
        }

        return 0;
}