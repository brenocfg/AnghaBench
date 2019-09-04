#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iskey; scalar_t__ iscompr; } ;
typedef  TYPE_1__ raxNode ;
typedef  int /*<<< orphan*/  rax ;

/* Variables and functions */
 int /*<<< orphan*/  debugf (char*,int,unsigned char*) ; 
 void* raxGetData (TYPE_1__*) ; 
 size_t raxLowWalk (int /*<<< orphan*/ *,unsigned char*,size_t,TYPE_1__**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 void* raxNotFound ; 

void *raxFind(rax *rax, unsigned char *s, size_t len) {
    raxNode *h;

    debugf("### Lookup: %.*s\n", (int)len, s);
    int splitpos = 0;
    size_t i = raxLowWalk(rax,s,len,&h,NULL,&splitpos,NULL);
    if (i != len || (h->iscompr && splitpos != 0) || !h->iskey)
        return raxNotFound;
    return raxGetData(h);
}