#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vaddr_t ;
struct TYPE_3__ {scalar_t__* leaves; } ;
typedef  TYPE_1__ MmuVsidTree ;

/* Variables and functions */
 int /*<<< orphan*/  printmap (int,scalar_t__) ; 

void dumptree(vaddr_t vaddr, MmuVsidTree *tree)
{
    int j;

    for (j = 0; j < 256; j++)
    {
        if (tree->leaves[j])
        {
            printmap(vaddr | (j << 12), tree->leaves[j]);
        }
    }
}