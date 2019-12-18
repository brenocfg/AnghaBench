#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; scalar_t__ dispatching; } ;
typedef  TYPE_1__ sd_event_source ;

/* Variables and functions */
 scalar_t__ SOURCE_IO ; 
 int /*<<< orphan*/  source_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  source_free (TYPE_1__*) ; 
 int /*<<< orphan*/  source_io_unregister (TYPE_1__*) ; 

__attribute__((used)) static sd_event_source* event_source_free(sd_event_source *s) {
        if (!s)
                return NULL;

        /* Here's a special hack: when we are called from a
         * dispatch handler we won't free the event source
         * immediately, but we will detach the fd from the
         * epoll. This way it is safe for the caller to unref
         * the event source and immediately close the fd, but
         * we still retain a valid event source object after
         * the callback. */

        if (s->dispatching) {
                if (s->type == SOURCE_IO)
                        source_io_unregister(s);

                source_disconnect(s);
        } else
                source_free(s);

        return NULL;
}