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
struct TYPE_3__ {int count; int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ sqliterk_values ;
typedef  int /*<<< orphan*/  sqliterk_value ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkValueClear (int /*<<< orphan*/ *) ; 

int sqliterkValuesClear(sqliterk_values *values)
{
    if (!values) {
        return SQLITERK_MISUSE;
    }

    int i;
    for (i = 0; i < values->count; i++) {
        sqliterk_value *value = &values->values[i];
        sqliterkValueClear(value);
    }
    values->count = 0;
    return SQLITERK_OK;
}