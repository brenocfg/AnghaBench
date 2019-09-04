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
typedef  int /*<<< orphan*/ * xmlRefTablePtr ;
typedef  int /*<<< orphan*/ * xmlListPtr ;
typedef  TYPE_1__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {scalar_t__ refs; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

xmlListPtr
xmlGetRefs(xmlDocPtr doc, const xmlChar *ID) {
    xmlRefTablePtr table;

    if (doc == NULL) {
        return(NULL);
    }

    if (ID == NULL) {
        return(NULL);
    }

    table = (xmlRefTablePtr) doc->refs;
    if (table == NULL)
        return(NULL);

    return (xmlHashLookup(table, ID));
}