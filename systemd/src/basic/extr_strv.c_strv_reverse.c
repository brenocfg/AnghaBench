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
 int /*<<< orphan*/  SWAP_TWO (char*,char*) ; 
 size_t strv_length (char**) ; 

char **strv_reverse(char **l) {
        size_t n, i;

        n = strv_length(l);
        if (n <= 1)
                return l;

        for (i = 0; i < n / 2; i++)
                SWAP_TWO(l[i], l[n-1-i]);

        return l;
}