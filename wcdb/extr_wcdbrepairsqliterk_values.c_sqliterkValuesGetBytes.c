#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* values; } ;
typedef  TYPE_4__ sqliterk_values ;
struct TYPE_10__ {TYPE_2__* text; TYPE_1__* binary; } ;
struct TYPE_12__ {int type; TYPE_3__ any; } ;
typedef  TYPE_5__ sqliterk_value ;
struct TYPE_9__ {int s; } ;
struct TYPE_8__ {int s; } ;

/* Variables and functions */
 int sqliterkValuesGetCount (TYPE_4__*) ; 
#define  sqliterk_value_type_binary 129 
#define  sqliterk_value_type_text 128 

int sqliterkValuesGetBytes(sqliterk_values *values, int index)
{
    int out = 0;
    if (values && index < sqliterkValuesGetCount(values)) {
        sqliterk_value *value = &values->values[index];
        switch (value->type) {
            case sqliterk_value_type_binary:
                out = value->any.binary->s;
                break;
            case sqliterk_value_type_text:
                out = value->any.text->s;
                break;
            default:
                break;
        }
    }
    return out;
}