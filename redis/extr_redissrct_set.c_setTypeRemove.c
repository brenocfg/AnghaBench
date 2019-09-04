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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_3__ {scalar_t__ encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ DICT_OK ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_INTSET ; 
 scalar_t__ dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictResize (int /*<<< orphan*/ ) ; 
 scalar_t__ htNeedsResize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intsetRemove (int /*<<< orphan*/ ,long long,int*) ; 
 scalar_t__ isSdsRepresentableAsLongLong (int /*<<< orphan*/ ,long long*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int setTypeRemove(robj *setobj, sds value) {
    long long llval;
    if (setobj->encoding == OBJ_ENCODING_HT) {
        if (dictDelete(setobj->ptr,value) == DICT_OK) {
            if (htNeedsResize(setobj->ptr)) dictResize(setobj->ptr);
            return 1;
        }
    } else if (setobj->encoding == OBJ_ENCODING_INTSET) {
        if (isSdsRepresentableAsLongLong(value,&llval) == C_OK) {
            int success;
            setobj->ptr = intsetRemove(setobj->ptr,llval,&success);
            if (success) return 1;
        }
    } else {
        serverPanic("Unknown set encoding");
    }
    return 0;
}