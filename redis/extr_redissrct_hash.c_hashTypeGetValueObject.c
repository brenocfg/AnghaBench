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
typedef  int /*<<< orphan*/  robj ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/ * createStringObject (char*,unsigned int) ; 
 int /*<<< orphan*/ * createStringObjectFromLongLong (long long) ; 
 scalar_t__ hashTypeGetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**,unsigned int*,long long*) ; 

robj *hashTypeGetValueObject(robj *o, sds field) {
    unsigned char *vstr;
    unsigned int vlen;
    long long vll;

    if (hashTypeGetValue(o,field,&vstr,&vlen,&vll) == C_ERR) return NULL;
    if (vstr) return createStringObject((char*)vstr,vlen);
    else return createStringObjectFromLongLong(vll);
}