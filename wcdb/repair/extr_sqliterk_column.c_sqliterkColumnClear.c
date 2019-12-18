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
struct TYPE_3__ {int /*<<< orphan*/  values; int /*<<< orphan*/  overflowPages; scalar_t__ rowid; } ;
typedef  TYPE_1__ sqliterk_column ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkValuesClear (int /*<<< orphan*/ ) ; 

int sqliterkColumnClear(sqliterk_column *column)
{
    if (!column) {
        return SQLITERK_MISUSE;
    }
    column->rowid = 0;
    sqliterkValuesClear(column->overflowPages);
    sqliterkValuesClear(column->values);
    return SQLITERK_OK;
}