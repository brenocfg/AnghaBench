#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_values ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_NOMEM ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/ * sqliterkOSMalloc (int) ; 
 int sqliterkValuesAutoGrow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkValuesFree (int /*<<< orphan*/ *) ; 

int sqliterkValuesAlloc(sqliterk_values **values)
{
    if (!values) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterk_values *theValues = sqliterkOSMalloc(sizeof(sqliterk_values));
    if (!theValues) {
        rc = SQLITERK_NOMEM;
        goto sqliterkValuesAlloc_Failed;
    }
    rc = sqliterkValuesAutoGrow(theValues);
    if (rc != SQLITERK_OK) {
        goto sqliterkValuesAlloc_Failed;
    }
    *values = theValues;
    return SQLITERK_OK;
sqliterkValuesAlloc_Failed:
    if (theValues) {
        sqliterkValuesFree(theValues);
    }
    return rc;
}