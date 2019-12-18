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
 scalar_t__* xmlStrndup (scalar_t__ const*,int) ; 

xmlChar *
xmlStrsub(const xmlChar *str, int start, int len) {
    int i;

    if (str == NULL) return(NULL);
    if (start < 0) return(NULL);
    if (len < 0) return(NULL);

    for (i = 0;i < start;i++) {
        if (*str == 0) return(NULL);
        str++;
    }
    if (*str == 0) return(NULL);
    return(xmlStrndup(str, len));
}