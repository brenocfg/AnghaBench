#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct d3dx_regstore {scalar_t__* tables; } ;
struct TYPE_2__ {unsigned int component_size; int type; } ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 double NAN ; 
#define  PRES_VT_DOUBLE 129 
#define  PRES_VT_FLOAT 128 
 TYPE_1__* table_info ; 

__attribute__((used)) static double regstore_get_double(struct d3dx_regstore *rs, unsigned int table, unsigned int offset)
{
    BYTE *p;

    p = (BYTE *)rs->tables[table] + table_info[table].component_size * offset;
    switch (table_info[table].type)
    {
        case PRES_VT_FLOAT:
            return *(float *)p;
        case PRES_VT_DOUBLE:
            return *(double *)p;
        default:
            FIXME("Unexpected preshader input from table %u.\n", table);
            return NAN;
    }
}