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
 int xmlStrEqual (scalar_t__ const*,scalar_t__ const*) ; 

int
xmlStrQEqual(const xmlChar *pref, const xmlChar *name, const xmlChar *str) {
    if (pref == NULL) return(xmlStrEqual(name, str));
    if (name == NULL) return(0);
    if (str == NULL) return(0);

    do {
        if (*pref++ != *str) return(0);
    } while ((*str++) && (*pref));
    if (*str++ != ':') return(0);
    do {
        if (*name++ != *str) return(0);
    } while (*str++);
    return(1);
}