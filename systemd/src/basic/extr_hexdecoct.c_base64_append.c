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
 int base64_append_width (char**,int,char*,int,void const*,size_t,int) ; 

int base64_append(
                char **prefix, int plen,
                const void *p, size_t l,
                int indent, int width) {

        if (plen > width / 2 || plen + indent > width)
                /* leave indent on the left, keep last column free */
                return base64_append_width(prefix, plen, "\n", indent, p, l, width - indent - 1);
        else
                /* leave plen on the left, keep last column free */
                return base64_append_width(prefix, plen, " ", plen, p, l, width - plen - 1);
}