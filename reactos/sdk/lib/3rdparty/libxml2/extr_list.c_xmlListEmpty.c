#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlListPtr ;
struct TYPE_5__ {TYPE_1__* sentinel; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */

int
xmlListEmpty(xmlListPtr l)
{
    if (l == NULL)
        return(-1);
    return (l->sentinel->next == l->sentinel);
}