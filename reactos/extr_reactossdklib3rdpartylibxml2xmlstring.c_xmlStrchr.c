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

const xmlChar *
xmlStrchr(const xmlChar *str, xmlChar val) {
    if (str == NULL) return(NULL);
    while (*str != 0) { /* non input consuming */
        if (*str == val) return((xmlChar *) str);
        str++;
    }
    return(NULL);
}