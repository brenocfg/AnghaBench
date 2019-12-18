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
 scalar_t__ dns_name_compare_func (char const*,char const*) ; 

int dns_name_between(const char *a, const char *b, const char *c) {
        /* Determine if b is strictly greater than a and strictly smaller than c.
           We consider the order of names to be circular, so that if a is
           strictly greater than c, we consider b to be between them if it is
           either greater than a or smaller than c. This is how the canonical
           DNS name order used in NSEC records work. */

        if (dns_name_compare_func(a, c) < 0)
                /*
                   a and c are properly ordered:
                   a<---b--->c
                */
                return dns_name_compare_func(a, b) < 0 &&
                       dns_name_compare_func(b, c) < 0;
        else
                /*
                   a and c are equal or 'reversed':
                   <--b--c         a----->
                   or:
                   <-----c         a--b-->
                */
                return dns_name_compare_func(b, c) < 0 ||
                       dns_name_compare_func(a, b) < 0;
}