#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ encoding; scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int C_OK ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 scalar_t__ OBJ_STRING ; 
 int isSdsRepresentableAsLongLong (scalar_t__,long long*) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

int isObjectRepresentableAsLongLong(robj *o, long long *llval) {
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
    if (o->encoding == OBJ_ENCODING_INT) {
        if (llval) *llval = (long) o->ptr;
        return C_OK;
    } else {
        return isSdsRepresentableAsLongLong(o->ptr,llval);
    }
}