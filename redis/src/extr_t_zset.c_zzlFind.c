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
typedef  scalar_t__ sds ;

/* Variables and functions */
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 scalar_t__ ziplistCompare (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistNext (unsigned char*,unsigned char*) ; 
 double zzlGetScore (unsigned char*) ; 

unsigned char *zzlFind(unsigned char *zl, sds ele, double *score) {
    unsigned char *eptr = ziplistIndex(zl,0), *sptr;

    while (eptr != NULL) {
        sptr = ziplistNext(zl,eptr);
        serverAssert(sptr != NULL);

        if (ziplistCompare(eptr,(unsigned char*)ele,sdslen(ele))) {
            /* Matching element, pull out score. */
            if (score != NULL) *score = zzlGetScore(sptr);
            return eptr;
        }

        /* Move to next element. */
        eptr = ziplistNext(zl,sptr);
    }
    return NULL;
}