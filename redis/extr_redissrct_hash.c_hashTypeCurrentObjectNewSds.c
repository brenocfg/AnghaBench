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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  hashTypeIterator ;

/* Variables and functions */
 int /*<<< orphan*/  hashTypeCurrentObject (int /*<<< orphan*/ *,int,unsigned char**,unsigned int*,long long*) ; 
 int /*<<< orphan*/  sdsfromlonglong (long long) ; 
 int /*<<< orphan*/  sdsnewlen (unsigned char*,unsigned int) ; 

sds hashTypeCurrentObjectNewSds(hashTypeIterator *hi, int what) {
    unsigned char *vstr;
    unsigned int vlen;
    long long vll;

    hashTypeCurrentObject(hi,what,&vstr,&vlen,&vll);
    if (vstr) return sdsnewlen(vstr,vlen);
    return sdsfromlonglong(vll);
}