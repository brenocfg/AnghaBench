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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  PRES_VT_BOOL 131 
#define  PRES_VT_DOUBLE 130 
#define  PRES_VT_FLOAT 129 
#define  PRES_VT_INT 128 
 int lrint (double) ; 
 TYPE_1__* table_info ; 

__attribute__((used)) static void regstore_set_double(struct d3dx_regstore *rs, unsigned int table, unsigned int offset, double v)
{
    BYTE *p;

    p = (BYTE *)rs->tables[table] + table_info[table].component_size * offset;
    switch (table_info[table].type)
    {
        case PRES_VT_FLOAT : *(float *)p = v; break;
        case PRES_VT_DOUBLE: *(double *)p = v; break;
        case PRES_VT_INT   : *(int *)p = lrint(v); break;
        case PRES_VT_BOOL  : *(BOOL *)p = !!v; break;
        default:
            FIXME("Bad type %u.\n", table_info[table].type);
            break;
    }
}