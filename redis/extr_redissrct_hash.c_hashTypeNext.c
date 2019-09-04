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
struct TYPE_5__ {scalar_t__ encoding; unsigned char* fptr; unsigned char* vptr; int /*<<< orphan*/  di; int /*<<< orphan*/ * de; TYPE_1__* subject; } ;
typedef  TYPE_2__ hashTypeIterator ;
struct TYPE_4__ {unsigned char* ptr; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 unsigned char* ziplistIndex (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* ziplistNext (unsigned char*,unsigned char*) ; 

int hashTypeNext(hashTypeIterator *hi) {
    if (hi->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *zl;
        unsigned char *fptr, *vptr;

        zl = hi->subject->ptr;
        fptr = hi->fptr;
        vptr = hi->vptr;

        if (fptr == NULL) {
            /* Initialize cursor */
            serverAssert(vptr == NULL);
            fptr = ziplistIndex(zl, 0);
        } else {
            /* Advance cursor */
            serverAssert(vptr != NULL);
            fptr = ziplistNext(zl, vptr);
        }
        if (fptr == NULL) return C_ERR;

        /* Grab pointer to the value (fptr points to the field) */
        vptr = ziplistNext(zl, fptr);
        serverAssert(vptr != NULL);

        /* fptr, vptr now point to the first or next pair */
        hi->fptr = fptr;
        hi->vptr = vptr;
    } else if (hi->encoding == OBJ_ENCODING_HT) {
        if ((hi->de = dictNext(hi->di)) == NULL) return C_ERR;
    } else {
        serverPanic("Unknown hash encoding");
    }
    return C_OK;
}