#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * memory; TYPE_2__* binary; TYPE_1__* text; } ;
struct TYPE_9__ {int type; TYPE_3__ any; } ;
typedef  TYPE_4__ sqliterk_value ;
struct TYPE_7__ {int /*<<< orphan*/ * b; } ;
struct TYPE_6__ {int /*<<< orphan*/ * t; } ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkOSFree (int /*<<< orphan*/ *) ; 
#define  sqliterk_value_type_binary 129 
 int sqliterk_value_type_null ; 
#define  sqliterk_value_type_text 128 

int sqliterkValueClear(sqliterk_value *value)
{
    if (!value) {
        return SQLITERK_MISUSE;
    }
    if (value->any.memory) {
        switch (value->type) {
            case sqliterk_value_type_text:
                if (value->any.text->t) {
                    sqliterkOSFree(value->any.text->t);
                    value->any.text->t = NULL;
                }
                break;
            case sqliterk_value_type_binary:
                if (value->any.binary->b) {
                    sqliterkOSFree(value->any.binary->b);
                    value->any.binary->b = NULL;
                }
                break;
            default:
                break;
        }
        sqliterkOSFree(value->any.memory);
        value->any.memory = NULL;
    }
    value->type = sqliterk_value_type_null;
    return SQLITERK_OK;
}