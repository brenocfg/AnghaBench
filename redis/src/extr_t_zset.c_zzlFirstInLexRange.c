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
typedef  int /*<<< orphan*/  zlexrangespec ;

/* Variables and functions */
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistNext (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  zzlIsInLexRange (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zzlLexValueGteMin (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zzlLexValueLteMax (unsigned char*,int /*<<< orphan*/ *) ; 

unsigned char *zzlFirstInLexRange(unsigned char *zl, zlexrangespec *range) {
    unsigned char *eptr = ziplistIndex(zl,0), *sptr;

    /* If everything is out of range, return early. */
    if (!zzlIsInLexRange(zl,range)) return NULL;

    while (eptr != NULL) {
        if (zzlLexValueGteMin(eptr,range)) {
            /* Check if score <= max. */
            if (zzlLexValueLteMax(eptr,range))
                return eptr;
            return NULL;
        }

        /* Move to next element. */
        sptr = ziplistNext(zl,eptr); /* This element score. Skip it. */
        serverAssert(sptr != NULL);
        eptr = ziplistNext(zl,sptr); /* Next element. */
    }

    return NULL;
}