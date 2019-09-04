#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ encoding; int /*<<< orphan*/  ii; TYPE_1__* subject; int /*<<< orphan*/  di; } ;
typedef  TYPE_2__ setTypeIterator ;
typedef  int /*<<< orphan*/ * sds ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/ * dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intsetGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int setTypeNext(setTypeIterator *si, sds *sdsele, int64_t *llele) {
    if (si->encoding == OBJ_ENCODING_HT) {
        dictEntry *de = dictNext(si->di);
        if (de == NULL) return -1;
        *sdsele = dictGetKey(de);
        *llele = -123456789; /* Not needed. Defensive. */
    } else if (si->encoding == OBJ_ENCODING_INTSET) {
        if (!intsetGet(si->subject->ptr,si->ii++,llele))
            return -1;
        *sdsele = NULL; /* Not needed. Defensive. */
    } else {
        serverPanic("Wrong set encoding in setTypeNext");
    }
    return si->encoding;
}