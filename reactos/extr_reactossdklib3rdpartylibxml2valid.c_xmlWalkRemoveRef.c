#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlRemoveMemoPtr ;
typedef  TYPE_2__* xmlRefPtr ;
typedef  int /*<<< orphan*/  xmlListPtr ;
typedef  scalar_t__ xmlAttrPtr ;
struct TYPE_4__ {scalar_t__ attr; } ;
struct TYPE_3__ {scalar_t__ ap; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlListRemoveFirst (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
xmlWalkRemoveRef(const void *data, void *user)
{
    xmlAttrPtr attr0 = ((xmlRefPtr)data)->attr;
    xmlAttrPtr attr1 = ((xmlRemoveMemoPtr)user)->ap;
    xmlListPtr ref_list = ((xmlRemoveMemoPtr)user)->l;

    if (attr0 == attr1) { /* Matched: remove and terminate walk */
        xmlListRemoveFirst(ref_list, (void *)data);
        return 0;
    }
    return 1;
}