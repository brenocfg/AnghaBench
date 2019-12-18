#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* values; } ;
typedef  TYPE_2__ sqliterk_values ;
typedef  int /*<<< orphan*/  sqliterk_value_type ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int sqliterkValuesGetCount (TYPE_2__*) ; 
 int /*<<< orphan*/  sqliterk_value_type_null ; 

sqliterk_value_type sqliterkValuesGetType(sqliterk_values *values, int index)
{
    if (values && index < sqliterkValuesGetCount(values)) {
        return values->values[index].type;
    }
    return sqliterk_value_type_null;
}