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
typedef  long long int64_t ;

/* Variables and functions */
 unsigned char* lpGet (unsigned char*,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int string2ll (char*,long long,long long*) ; 

int64_t lpGetInteger(unsigned char *ele) {
    int64_t v;
    unsigned char *e = lpGet(ele,&v,NULL);
    if (e == NULL) return v;
    /* The following code path should never be used for how listpacks work:
     * they should always be able to store an int64_t value in integer
     * encoded form. However the implementation may change. */
    long long ll;
    int retval = string2ll((char*)e,v,&ll);
    serverAssert(retval != 0);
    v = ll;
    return v;
}