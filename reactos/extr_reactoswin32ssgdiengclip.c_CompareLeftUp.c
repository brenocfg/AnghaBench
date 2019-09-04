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
struct TYPE_4__ {scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ RECTL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static __inline int
CompareLeftUp(
    const RECTL *r1,
    const RECTL *r2)
{
    int Cmp;

    if (r1->bottom < r2->bottom)
    {
        Cmp = +1;
    }
    else if (r2->bottom < r1->bottom)
    {
        Cmp = -1;
    }
    else
    {
        ASSERT(r1->top == r2->top);
        if (r1->right < r2->right)
        {
            Cmp = +1;
        }
        else if (r2->right < r1->right)
        {
            Cmp = -1;
        }
        else
        {
            ASSERT(r1->left == r2->left);
            Cmp = 0;
        }
    }
    return Cmp;
}