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
struct TYPE_3__ {scalar_t__ encoding; scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  intset ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int intsetFind (int /*<<< orphan*/ *,long long) ; 
 scalar_t__ isSdsRepresentableAsLongLong (int /*<<< orphan*/ ,long long*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int setTypeIsMember(robj *subject, sds value) {
    long long llval;
    if (subject->encoding == OBJ_ENCODING_HT) {
        return dictFind((dict*)subject->ptr,value) != NULL;
    } else if (subject->encoding == OBJ_ENCODING_INTSET) {
        if (isSdsRepresentableAsLongLong(value,&llval) == C_OK) {
            return intsetFind((intset*)subject->ptr,llval);
        }
    } else {
        serverPanic("Unknown set encoding");
    }
    return 0;
}