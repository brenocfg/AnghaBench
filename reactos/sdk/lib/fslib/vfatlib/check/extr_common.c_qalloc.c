#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* data; void* next; } ;
typedef  TYPE_1__ LINK ;

/* Variables and functions */
 void* alloc (int) ; 
 void* vfalloc (int) ; 

void *qalloc(void **root, int size)
{
    LINK *link;

#ifndef __REACTOS__
    link = alloc(sizeof(LINK));
#else
    link = vfalloc(sizeof(LINK));
#endif
    link->next = *root;
    *root = link;
#ifndef __REACTOS__
    return link->data = alloc(size);
#else
    return link->data = vfalloc(size);
#endif
}