#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  setTypeIterator ;
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  OBJ_ENCODING_HT 129 
#define  OBJ_ENCODING_INTSET 128 
 int /*<<< orphan*/ * sdsdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdsfromlonglong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int setTypeNext (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

sds setTypeNextObject(setTypeIterator *si) {
    int64_t intele;
    sds sdsele;
    int encoding;

    encoding = setTypeNext(si,&sdsele,&intele);
    switch(encoding) {
        case -1:    return NULL;
        case OBJ_ENCODING_INTSET:
            return sdsfromlonglong(intele);
        case OBJ_ENCODING_HT:
            return sdsdup(sdsele);
        default:
            serverPanic("Unsupported encoding");
    }
    return NULL; /* just to suppress warnings */
}