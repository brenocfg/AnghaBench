#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {scalar_t__ encoding; scalar_t__ length; } ;
typedef  TYPE_1__ intset ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _intsetSet (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _intsetValueEncoding (int /*<<< orphan*/ ) ; 
 scalar_t__ intrev32ifbe (scalar_t__) ; 
 int /*<<< orphan*/  intsetMoveTail (TYPE_1__*,scalar_t__,scalar_t__) ; 
 TYPE_1__* intsetResize (TYPE_1__*,scalar_t__) ; 
 scalar_t__ intsetSearch (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__* intsetUpgradeAndAdd (TYPE_1__*,int /*<<< orphan*/ ) ; 

intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {
    uint8_t valenc = _intsetValueEncoding(value);
    uint32_t pos;
    if (success) *success = 1;

    /* Upgrade encoding if necessary. If we need to upgrade, we know that
     * this value should be either appended (if > 0) or prepended (if < 0),
     * because it lies outside the range of existing values. */
    if (valenc > intrev32ifbe(is->encoding)) {
        /* This always succeeds, so we don't need to curry *success. */
        return intsetUpgradeAndAdd(is,value);
    } else {
        /* Abort if the value is already present in the set.
         * This call will populate "pos" with the right position to insert
         * the value when it cannot be found. */
        if (intsetSearch(is,value,&pos)) {
            if (success) *success = 0;
            return is;
        }

        is = intsetResize(is,intrev32ifbe(is->length)+1);
        if (pos < intrev32ifbe(is->length)) intsetMoveTail(is,pos,pos+1);
    }

    _intsetSet(is,pos,value);
    is->length = intrev32ifbe(intrev32ifbe(is->length)+1);
    return is;
}