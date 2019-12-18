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
struct TYPE_5__ {int /*<<< orphan*/  overflowPages; int /*<<< orphan*/  values; } ;
typedef  TYPE_1__ sqliterk_column ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_NOMEM ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkColumnFree (TYPE_1__*) ; 
 TYPE_1__* sqliterkOSMalloc (int) ; 
 int sqliterkValuesAlloc (int /*<<< orphan*/ *) ; 

int sqliterkColumnAlloc(sqliterk_column **column)
{
    if (!column) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterk_column *theColumn = sqliterkOSMalloc(sizeof(sqliterk_column));
    if (!theColumn) {
        rc = SQLITERK_NOMEM;
        goto sqliterkColumnAlloc_Failed;
    }
    rc = sqliterkValuesAlloc(&theColumn->values);
    if (rc != SQLITERK_OK) {
        goto sqliterkColumnAlloc_Failed;
    }
    rc = sqliterkValuesAlloc(&theColumn->overflowPages);
    if (rc != SQLITERK_OK) {
        goto sqliterkColumnAlloc_Failed;
    }
    *column = theColumn;
    return SQLITERK_OK;

sqliterkColumnAlloc_Failed:
    if (theColumn) {
        sqliterkColumnFree(theColumn);
    }
    *column = NULL;
    return rc;
}