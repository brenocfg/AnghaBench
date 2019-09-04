#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int encoding; int length; } ;
typedef  TYPE_1__ intset ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ _intsetValueEncoding (int /*<<< orphan*/ ) ; 
 scalar_t__ intrev32ifbe (int) ; 
 int /*<<< orphan*/  intsetMoveTail (TYPE_1__*,int,int) ; 
 TYPE_1__* intsetResize (TYPE_1__*,int) ; 
 scalar_t__ intsetSearch (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

intset *intsetRemove(intset *is, int64_t value, int *success) {
    uint8_t valenc = _intsetValueEncoding(value);
    uint32_t pos;
    if (success) *success = 0;

    if (valenc <= intrev32ifbe(is->encoding) && intsetSearch(is,value,&pos)) {
        uint32_t len = intrev32ifbe(is->length);

        /* We know we can delete */
        if (success) *success = 1;

        /* Overwrite value with tail and update length */
        if (pos < (len-1)) intsetMoveTail(is,pos+1,pos);
        is = intsetResize(is,len-1);
        is->length = intrev32ifbe(len-1);
    }
    return is;
}