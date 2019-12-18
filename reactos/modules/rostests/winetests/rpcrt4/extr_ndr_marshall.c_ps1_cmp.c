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
struct TYPE_2__ {scalar_t__ l1; scalar_t__* pl1; scalar_t__* pc1; } ;
typedef  TYPE_1__ ps1_t ;

/* Variables and functions */

__attribute__((used)) static int ps1_cmp(const void *s1, const void *s2, size_t num)
{
    const ps1_t *p1, *p2;

    p1 = s1;
    p2 = s2;

    if(p1->l1 != p2->l1)
        return 1;

    if(p1->pl1 && p2->pl1)
    {
        if(*p1->pl1 != *p2->pl1)
            return 1;
    }
    else if(p1->pl1 || p2->pl1)
        return 1;

    if(p1->pc1 && p2->pc1)
    {
        if(*p1->pc1 != *p2->pc1)
            return 1;
    }
    else if(p1->pc1 || p2->pc1)
        return 1;

    return 0;
}