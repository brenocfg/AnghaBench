#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
struct TYPE_5__ {struct TYPE_5__* sentinel; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlListClear (TYPE_1__*) ; 

void xmlListDelete(xmlListPtr l)
{
    if (l == NULL)
        return;

    xmlListClear(l);
    xmlFree(l->sentinel);
    xmlFree(l);
}