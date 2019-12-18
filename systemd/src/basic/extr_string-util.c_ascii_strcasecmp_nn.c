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
 int CMP (size_t,size_t) ; 
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int ascii_strcasecmp_n (char const*,char const*,int /*<<< orphan*/ ) ; 

int ascii_strcasecmp_nn(const char *a, size_t n, const char *b, size_t m) {
        int r;

        r = ascii_strcasecmp_n(a, b, MIN(n, m));
        if (r != 0)
                return r;

        return CMP(n, m);
}