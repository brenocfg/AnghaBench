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
typedef  int /*<<< orphan*/  quicklist ;
typedef  int /*<<< orphan*/  longstr ;

/* Variables and functions */
 unsigned int ll2string (char*,int,long long) ; 
 int /*<<< orphan*/  quicklistPushTail (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 scalar_t__ ziplistGet (unsigned char*,unsigned char**,unsigned int*,long long*) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistNext (unsigned char*,unsigned char*) ; 

quicklist *quicklistAppendValuesFromZiplist(quicklist *quicklist,
                                            unsigned char *zl) {
    unsigned char *value;
    unsigned int sz;
    long long longval;
    char longstr[32] = {0};

    unsigned char *p = ziplistIndex(zl, 0);
    while (ziplistGet(p, &value, &sz, &longval)) {
        if (!value) {
            /* Write the longval as a string so we can re-add it */
            sz = ll2string(longstr, sizeof(longstr), longval);
            value = (unsigned char *)longstr;
        }
        quicklistPushTail(quicklist, value, sz);
        p = ziplistNext(zl, p);
    }
    zfree(zl);
    return quicklist;
}