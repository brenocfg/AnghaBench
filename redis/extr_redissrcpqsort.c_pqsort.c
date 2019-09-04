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

/* Variables and functions */
 int /*<<< orphan*/  _pqsort (void*,size_t,size_t,int (*) (void const*,void const*),unsigned char*,unsigned char*) ; 

void
pqsort(void *a, size_t n, size_t es,
    int (*cmp) (const void *, const void *), size_t lrange, size_t rrange)
{
    _pqsort(a,n,es,cmp,((unsigned char*)a)+(lrange*es),
                       ((unsigned char*)a)+((rrange+1)*es)-1);
}