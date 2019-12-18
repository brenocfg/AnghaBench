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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  reply_callbacks; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 scalar_t__ COOKIE_CYCLED ; 
 int EBUSY ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cookie_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int next_cookie(sd_bus *b) {
        uint64_t new_cookie;

        assert(b);

        new_cookie = cookie_inc(b->cookie);

        /* Small optimization: don't bother with checking for cookie reuse until we overran cookiespace at
         * least once, but then do it thorougly. */
        if (FLAGS_SET(new_cookie, COOKIE_CYCLED)) {
                uint32_t i;

                /* Check if the cookie is currently in use. If so, pick the next one */
                for (i = 0; i < COOKIE_CYCLED; i++) {
                        if (!ordered_hashmap_contains(b->reply_callbacks, &new_cookie))
                                goto good;

                        new_cookie = cookie_inc(new_cookie);
                }

                /* Can't fulfill request */
                return -EBUSY;
        }

good:
        b->cookie = new_cookie;
        return 0;
}