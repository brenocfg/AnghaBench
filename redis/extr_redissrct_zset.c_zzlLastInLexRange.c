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
 unsigned char* ziplistIndex (unsigned char*,int) ; 
 unsigned char* ziplistPrev (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  zzlIsInLexRange (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zzlLexValueGteMin (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zzlLexValueLteMax (unsigned char*,int /*<<< orphan*/ *) ; 

unsigned char *zzlLastInLexRange(unsigned char *zl, zlexrangespec *range) {
    unsigned char *eptr = ziplistIndex(zl,-2), *sptr;

    /* If everything is out of range, return early. */
    if (!zzlIsInLexRange(zl,range)) return NULL;

    while (eptr != NULL) {
        if (zzlLexValueLteMax(eptr,range)) {
            /* Check if score >= min. */
            if (zzlLexValueGteMin(eptr,range))
                return eptr;
            return NULL;
        }

        /* Move to previous element by moving to the score of previous element.
         * When this returns NULL, we know there also is no element. */
        sptr = ziplistPrev(zl,eptr);
        if (sptr != NULL)
            serverAssert((eptr = ziplistPrev(zl,sptr)) != NULL);
        else
            eptr = NULL;
    }

    return NULL;
}