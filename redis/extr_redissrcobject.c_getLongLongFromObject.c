#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; scalar_t__ encoding; scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 scalar_t__ OBJ_STRING ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 scalar_t__ string2ll (scalar_t__,int /*<<< orphan*/ ,long long*) ; 

int getLongLongFromObject(robj *o, long long *target) {
    long long value;

    if (o == NULL) {
        value = 0;
    } else {
        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
        if (sdsEncodedObject(o)) {
            if (string2ll(o->ptr,sdslen(o->ptr),&value) == 0) return C_ERR;
        } else if (o->encoding == OBJ_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            serverPanic("Unknown string encoding");
        }
    }
    if (target) *target = value;
    return C_OK;
}