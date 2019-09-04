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
struct TYPE_4__ {scalar_t__ values; scalar_t__ overflowPages; } ;
typedef  TYPE_1__ sqliterk_column ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkOSFree (TYPE_1__*) ; 
 int /*<<< orphan*/  sqliterkValuesFree (scalar_t__) ; 

int sqliterkColumnFree(sqliterk_column *column)
{
    if (!column) {
        return SQLITERK_MISUSE;
    }
    if (column->overflowPages) {
        sqliterkValuesFree(column->overflowPages);
    }
    if (column->values) {
        sqliterkValuesFree(column->values);
    }
    sqliterkOSFree(column);
    return SQLITERK_OK;
}