#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
typedef  TYPE_2__* xmlLinkPtr ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {scalar_t__ (* linkCompare ) (int /*<<< orphan*/ ,void*) ;TYPE_2__* sentinel; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 
 TYPE_2__* xmlListLowerSearch (TYPE_1__*,void*) ; 

__attribute__((used)) static xmlLinkPtr
xmlListLinkSearch(xmlListPtr l, void *data)
{
    xmlLinkPtr lk;
    if (l == NULL)
        return(NULL);
    lk = xmlListLowerSearch(l, data);
    if (lk == l->sentinel)
        return NULL;
    else {
        if (l->linkCompare(lk->data, data) ==0)
            return lk;
        return NULL;
    }
}