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
 int xmlStrlen (scalar_t__ const*) ; 
 int /*<<< orphan*/  xmlStrncmp (scalar_t__ const*,scalar_t__ const*,int) ; 

const xmlChar *
xmlStrstr(const xmlChar *str, const xmlChar *val) {
    int n;

    if (str == NULL) return(NULL);
    if (val == NULL) return(NULL);
    n = xmlStrlen(val);

    if (n == 0) return(str);
    while (*str != 0) { /* non input consuming */
        if (*str == *val) {
            if (!xmlStrncmp(str, val, n)) return((const xmlChar *) str);
        }
        str++;
    }
    return(NULL);
}