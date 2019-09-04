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
typedef  scalar_t__ xmlChar ;

/* Variables and functions */

int
xmlStrlen(const xmlChar *str) {
    int len = 0;

    if (str == NULL) return(0);
    while (*str != 0) { /* non input consuming */
        str++;
        len++;
    }
    return(len);
}