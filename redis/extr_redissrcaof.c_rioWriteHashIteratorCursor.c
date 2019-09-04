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
typedef  char* sds ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_5__ {scalar_t__ encoding; } ;
typedef  TYPE_1__ hashTypeIterator ;

/* Variables and functions */
 long long LLONG_MAX ; 
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 unsigned int UINT_MAX ; 
 char* hashTypeCurrentFromHashTable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hashTypeCurrentFromZiplist (TYPE_1__*,int,unsigned char**,unsigned int*,long long*) ; 
 int rioWriteBulkLongLong (int /*<<< orphan*/ *,long long) ; 
 int rioWriteBulkString (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int sdslen (char*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

__attribute__((used)) static int rioWriteHashIteratorCursor(rio *r, hashTypeIterator *hi, int what) {
    if (hi->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *vstr = NULL;
        unsigned int vlen = UINT_MAX;
        long long vll = LLONG_MAX;

        hashTypeCurrentFromZiplist(hi, what, &vstr, &vlen, &vll);
        if (vstr)
            return rioWriteBulkString(r, (char*)vstr, vlen);
        else
            return rioWriteBulkLongLong(r, vll);
    } else if (hi->encoding == OBJ_ENCODING_HT) {
        sds value = hashTypeCurrentFromHashTable(hi, what);
        return rioWriteBulkString(r, value, sdslen(value));
    }

    serverPanic("Unknown hash encoding");
    return 0;
}