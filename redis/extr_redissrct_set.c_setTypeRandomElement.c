#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_3__ {scalar_t__ encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/ * dictGetFairRandomKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetKey (int /*<<< orphan*/ *) ; 
 int intsetRandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int setTypeRandomElement(robj *setobj, sds *sdsele, int64_t *llele) {
    if (setobj->encoding == OBJ_ENCODING_HT) {
        dictEntry *de = dictGetFairRandomKey(setobj->ptr);
        *sdsele = dictGetKey(de);
        *llele = -123456789; /* Not needed. Defensive. */
    } else if (setobj->encoding == OBJ_ENCODING_INTSET) {
        *llele = intsetRandom(setobj->ptr);
        *sdsele = NULL; /* Not needed. Defensive. */
    } else {
        serverPanic("Unknown set encoding");
    }
    return setobj->encoding;
}