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
struct in_addr_data {int dummy; } ;
typedef  int /*<<< orphan*/  OrderedSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int ordered_set_put_in_addr_data (int /*<<< orphan*/ *,struct in_addr_data const*) ; 

__attribute__((used)) static int ordered_set_put_in_addr_datav(OrderedSet *s, const struct in_addr_data *addresses, unsigned n) {
        int r, c = 0;
        unsigned i;

        assert(s);
        assert(addresses || n == 0);

        for (i = 0; i < n; i++) {
                r = ordered_set_put_in_addr_data(s, addresses+i);
                if (r < 0)
                        return r;

                c += r;
        }

        return c;
}