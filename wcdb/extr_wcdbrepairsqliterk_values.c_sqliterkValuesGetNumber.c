#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* values; } ;
typedef  TYPE_3__ sqliterk_values ;
struct TYPE_9__ {TYPE_1__* text; scalar_t__* number; scalar_t__* integer; } ;
struct TYPE_11__ {TYPE_2__ any; } ;
typedef  TYPE_4__ sqliterk_value ;
struct TYPE_8__ {int /*<<< orphan*/  t; } ;

/* Variables and functions */
 double atof (int /*<<< orphan*/ ) ; 
 int sqliterkValuesGetCount (TYPE_3__*) ; 
 int sqliterkValuesGetType (TYPE_3__*,int) ; 
#define  sqliterk_value_type_integer 130 
#define  sqliterk_value_type_number 129 
#define  sqliterk_value_type_text 128 

double sqliterkValuesGetNumber(sqliterk_values *values, int index)
{
    double out = 0;
    if (values && index < sqliterkValuesGetCount(values)) {
        sqliterk_value *value = &values->values[index];
        switch (sqliterkValuesGetType(values, index)) {
            case sqliterk_value_type_integer:
                out = (double) (*value->any.integer);
                break;
            case sqliterk_value_type_number:
                out = (double) (*value->any.number);
                break;
            case sqliterk_value_type_text:
                out = atof(value->any.text->t);
                break;
            default:
                break;
        }
    }
    return out;
}