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

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 int /*<<< orphan*/  ZIPLIST_HEAD ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 unsigned char* ziplistFind (unsigned char*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int ziplistGet (unsigned char*,unsigned char**,unsigned int*,long long*) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistNext (unsigned char*,unsigned char*) ; 

int hashTypeGetFromZiplist(robj *o, sds field,
                           unsigned char **vstr,
                           unsigned int *vlen,
                           long long *vll)
{
    unsigned char *zl, *fptr = NULL, *vptr = NULL;
    int ret;

    serverAssert(o->encoding == OBJ_ENCODING_ZIPLIST);

    zl = o->ptr;
    fptr = ziplistIndex(zl, ZIPLIST_HEAD);
    if (fptr != NULL) {
        fptr = ziplistFind(fptr, (unsigned char*)field, sdslen(field), 1);
        if (fptr != NULL) {
            /* Grab pointer to the value (fptr points to the field) */
            vptr = ziplistNext(zl, fptr);
            serverAssert(vptr != NULL);
        }
    }

    if (vptr != NULL) {
        ret = ziplistGet(vptr, vstr, vlen, vll);
        serverAssert(ret);
        return 0;
    }

    return -1;
}