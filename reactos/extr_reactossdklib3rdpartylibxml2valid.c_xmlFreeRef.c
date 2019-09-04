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
typedef  TYPE_1__* xmlRefPtr ;
typedef  int /*<<< orphan*/  xmlLinkPtr ;
struct TYPE_4__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlLinkGetData (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xmlFreeRef(xmlLinkPtr lk) {
    xmlRefPtr ref = (xmlRefPtr)xmlLinkGetData(lk);
    if (ref == NULL) return;
    if (ref->value != NULL)
        xmlFree((xmlChar *)ref->value);
    if (ref->name != NULL)
        xmlFree((xmlChar *)ref->name);
    xmlFree(ref);
}