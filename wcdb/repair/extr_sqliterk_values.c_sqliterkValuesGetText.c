#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* values; } ;
typedef  TYPE_3__ sqliterk_values ;
struct TYPE_8__ {TYPE_1__* text; } ;
struct TYPE_10__ {int type; TYPE_2__ any; } ;
typedef  TYPE_4__ sqliterk_value ;
struct TYPE_7__ {char* t; } ;

/* Variables and functions */
 int sqliterkValuesGetCount (TYPE_3__*) ; 
#define  sqliterk_value_type_text 128 

const char *sqliterkValuesGetText(sqliterk_values *values, int index)
{
    char *out = NULL;
    if (values && index < sqliterkValuesGetCount(values)) {
        sqliterk_value *value = &values->values[index];
        switch (value->type) {
            case sqliterk_value_type_text:
                out = value->any.text->t;
                break;
            default:
                break;
        }
    }
    return out;
}