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
typedef  char xmlChar ;

/* Variables and functions */

int
xmlCheckLanguageID(const xmlChar * lang)
{
    const xmlChar *cur = lang, *nxt;

    if (cur == NULL)
        return (0);
    if (((cur[0] == 'i') && (cur[1] == '-')) ||
        ((cur[0] == 'I') && (cur[1] == '-')) ||
        ((cur[0] == 'x') && (cur[1] == '-')) ||
        ((cur[0] == 'X') && (cur[1] == '-'))) {
        /*
         * Still allow IANA code and user code which were coming
         * from the previous version of the XML-1.0 specification
         * it's deprecated but we should not fail
         */
        cur += 2;
        while (((cur[0] >= 'A') && (cur[0] <= 'Z')) ||
               ((cur[0] >= 'a') && (cur[0] <= 'z')))
            cur++;
        return(cur[0] == 0);
    }
    nxt = cur;
    while (((nxt[0] >= 'A') && (nxt[0] <= 'Z')) ||
           ((nxt[0] >= 'a') && (nxt[0] <= 'z')))
           nxt++;
    if (nxt - cur >= 4) {
        /*
         * Reserved
         */
        if ((nxt - cur > 8) || (nxt[0] != 0))
            return(0);
        return(1);
    }
    if (nxt - cur < 2)
        return(0);
    /* we got an ISO 639 code */
    if (nxt[0] == 0)
        return(1);
    if (nxt[0] != '-')
        return(0);

    nxt++;
    cur = nxt;
    /* now we can have extlang or script or region or variant */
    if ((nxt[0] >= '0') && (nxt[0] <= '9'))
        goto region_m49;

    while (((nxt[0] >= 'A') && (nxt[0] <= 'Z')) ||
           ((nxt[0] >= 'a') && (nxt[0] <= 'z')))
           nxt++;
    if (nxt - cur == 4)
        goto script;
    if (nxt - cur == 2)
        goto region;
    if ((nxt - cur >= 5) && (nxt - cur <= 8))
        goto variant;
    if (nxt - cur != 3)
        return(0);
    /* we parsed an extlang */
    if (nxt[0] == 0)
        return(1);
    if (nxt[0] != '-')
        return(0);

    nxt++;
    cur = nxt;
    /* now we can have script or region or variant */
    if ((nxt[0] >= '0') && (nxt[0] <= '9'))
        goto region_m49;

    while (((nxt[0] >= 'A') && (nxt[0] <= 'Z')) ||
           ((nxt[0] >= 'a') && (nxt[0] <= 'z')))
           nxt++;
    if (nxt - cur == 2)
        goto region;
    if ((nxt - cur >= 5) && (nxt - cur <= 8))
        goto variant;
    if (nxt - cur != 4)
        return(0);
    /* we parsed a script */
script:
    if (nxt[0] == 0)
        return(1);
    if (nxt[0] != '-')
        return(0);

    nxt++;
    cur = nxt;
    /* now we can have region or variant */
    if ((nxt[0] >= '0') && (nxt[0] <= '9'))
        goto region_m49;

    while (((nxt[0] >= 'A') && (nxt[0] <= 'Z')) ||
           ((nxt[0] >= 'a') && (nxt[0] <= 'z')))
           nxt++;

    if ((nxt - cur >= 5) && (nxt - cur <= 8))
        goto variant;
    if (nxt - cur != 2)
        return(0);
    /* we parsed a region */
region:
    if (nxt[0] == 0)
        return(1);
    if (nxt[0] != '-')
        return(0);

    nxt++;
    cur = nxt;
    /* now we can just have a variant */
    while (((nxt[0] >= 'A') && (nxt[0] <= 'Z')) ||
           ((nxt[0] >= 'a') && (nxt[0] <= 'z')))
           nxt++;

    if ((nxt - cur < 5) || (nxt - cur > 8))
        return(0);

    /* we parsed a variant */
variant:
    if (nxt[0] == 0)
        return(1);
    if (nxt[0] != '-')
        return(0);
    /* extensions and private use subtags not checked */
    return (1);

region_m49:
    if (((nxt[1] >= '0') && (nxt[1] <= '9')) &&
        ((nxt[2] >= '0') && (nxt[2] <= '9'))) {
        nxt += 3;
        goto region;
    }
    return(0);
}