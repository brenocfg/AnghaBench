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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_5__ {scalar_t__ encoding; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 long long LLONG_MAX ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/ * hashTypeGetFromHashTable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hashTypeGetFromZiplist (TYPE_1__*,int /*<<< orphan*/ ,unsigned char**,unsigned int*,long long*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int hashTypeExists(robj *o, sds field) {
    if (o->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *vstr = NULL;
        unsigned int vlen = UINT_MAX;
        long long vll = LLONG_MAX;

        if (hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll) == 0) return 1;
    } else if (o->encoding == OBJ_ENCODING_HT) {
        if (hashTypeGetFromHashTable(o, field) != NULL) return 1;
    } else {
        serverPanic("Unknown hash encoding");
    }
    return 0;
}