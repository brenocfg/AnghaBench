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
typedef  scalar_t__ sds ;
struct TYPE_3__ {scalar_t__ encoding; unsigned char* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 int /*<<< orphan*/  ZIPLIST_HEAD ; 
 scalar_t__ dictDelete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dictResize (unsigned char*) ; 
 scalar_t__ htNeedsResize (unsigned char*) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 unsigned char* ziplistDelete (unsigned char*,unsigned char**) ; 
 unsigned char* ziplistFind (unsigned char*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 

int hashTypeDelete(robj *o, sds field) {
    int deleted = 0;

    if (o->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *zl, *fptr;

        zl = o->ptr;
        fptr = ziplistIndex(zl, ZIPLIST_HEAD);
        if (fptr != NULL) {
            fptr = ziplistFind(fptr, (unsigned char*)field, sdslen(field), 1);
            if (fptr != NULL) {
                zl = ziplistDelete(zl,&fptr); /* Delete the key. */
                zl = ziplistDelete(zl,&fptr); /* Delete the value. */
                o->ptr = zl;
                deleted = 1;
            }
        }
    } else if (o->encoding == OBJ_ENCODING_HT) {
        if (dictDelete((dict*)o->ptr, field) == C_OK) {
            deleted = 1;

            /* Always check if the dictionary needs a resize after a delete. */
            if (htNeedsResize(o->ptr)) dictResize(o->ptr);
        }

    } else {
        serverPanic("Unknown hash encoding");
    }
    return deleted;
}