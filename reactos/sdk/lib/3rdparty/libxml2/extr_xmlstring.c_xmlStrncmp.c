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
typedef  int xmlChar ;

/* Variables and functions */
 int strncmp (char const*,char const*,int) ; 

int
xmlStrncmp(const xmlChar *str1, const xmlChar *str2, int len) {
    register int tmp;

    if (len <= 0) return(0);
    if (str1 == str2) return(0);
    if (str1 == NULL) return(-1);
    if (str2 == NULL) return(1);
#ifdef __GNUC__
    tmp = strncmp((const char *)str1, (const char *)str2, len);
    return tmp;
#else
    do {
        tmp = *str1++ - *str2;
        if (tmp != 0 || --len == 0) return(tmp);
    } while (*str2++ != 0);
    return 0;
#endif
}