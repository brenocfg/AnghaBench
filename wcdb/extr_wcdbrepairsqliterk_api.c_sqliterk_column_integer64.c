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
typedef  int /*<<< orphan*/  sqliterk_column ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  sqliterkColumnGetValues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkValuesGetInteger64 (int /*<<< orphan*/ ,int) ; 

int64_t sqliterk_column_integer64(sqliterk_column *column, int index)
{
    return sqliterkValuesGetInteger64(sqliterkColumnGetValues(column), index);
}