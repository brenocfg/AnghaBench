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
typedef  int UINT ;
struct TYPE_3__ {scalar_t__* objectHandle; } ;
typedef  scalar_t__ HGDIOBJ ;
typedef  TYPE_1__ HANDLETABLE ;

/* Variables and functions */

__attribute__((used)) static int MF_AddHandle(HANDLETABLE *ht, UINT htlen, HGDIOBJ hobj)
{
    int i;

    for (i = 0; i < htlen; i++)
    {
	if (*(ht->objectHandle + i) == 0)
	{
	    *(ht->objectHandle + i) = hobj;
	    return i;
	}
    }
    return -1;
}