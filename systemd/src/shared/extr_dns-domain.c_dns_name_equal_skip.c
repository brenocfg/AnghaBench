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

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_name_equal (char const*,char const*) ; 
 int dns_name_skip (char const*,unsigned int,char const**) ; 

int dns_name_equal_skip(const char *a, unsigned n_labels, const char *b) {
        int r;

        assert(a);
        assert(b);

        r = dns_name_skip(a, n_labels, &a);
        if (r <= 0)
                return r;

        return dns_name_equal(a, b);
}