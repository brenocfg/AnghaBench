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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  OrderedSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int ordered_set_put_in4_addr (int /*<<< orphan*/ *,struct in_addr const*) ; 

__attribute__((used)) static int ordered_set_put_in4_addrv(OrderedSet *s,
                                     const struct in_addr *addresses,
                                     size_t n,
                                     bool (*predicate)(const struct in_addr *addr)) {
        int r, c = 0;
        size_t i;

        assert(s);
        assert(n == 0 || addresses);

        for (i = 0; i < n; i++) {
                if (predicate && !predicate(&addresses[i]))
                        continue;
                r = ordered_set_put_in4_addr(s, addresses+i);
                if (r < 0)
                        return r;

                c += r;
        }

        return c;
}