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
typedef  scalar_t__ xmlNotationTablePtr ;
typedef  int /*<<< orphan*/ * xmlNotationPtr ;
typedef  TYPE_1__* xmlDtdPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {int /*<<< orphan*/ * notations; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlHashLookup (scalar_t__,int /*<<< orphan*/  const*) ; 

xmlNotationPtr
xmlGetDtdNotationDesc(xmlDtdPtr dtd, const xmlChar *name) {
    xmlNotationTablePtr table;

    if (dtd == NULL) return(NULL);
    if (dtd->notations == NULL) return(NULL);
    table = (xmlNotationTablePtr) dtd->notations;

    return(xmlHashLookup(table, name));
}