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
struct d3dx_pres_reg {int table; int /*<<< orphan*/  offset; } ;
typedef  enum pres_reg_tables { ____Placeholder_pres_reg_tables } pres_reg_tables ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
#define  PRES_REGTAB_CONST 134 
#define  PRES_REGTAB_COUNT 133 
#define  PRES_REGTAB_IMMED 132 
#define  PRES_REGTAB_OBCONST 131 
#define  PRES_REGTAB_OCONST 130 
#define  PRES_REGTAB_OICONST 129 
#define  PRES_REGTAB_TEMP 128 

__attribute__((used)) static unsigned int *parse_pres_reg(unsigned int *ptr, struct d3dx_pres_reg *reg)
{
    static const enum pres_reg_tables reg_table[8] =
    {
        PRES_REGTAB_COUNT, PRES_REGTAB_IMMED, PRES_REGTAB_CONST, PRES_REGTAB_COUNT,
        PRES_REGTAB_OCONST, PRES_REGTAB_OBCONST, PRES_REGTAB_OICONST, PRES_REGTAB_TEMP
    };

    if (*ptr >= ARRAY_SIZE(reg_table) || reg_table[*ptr] == PRES_REGTAB_COUNT)
    {
        FIXME("Unsupported register table %#x.\n", *ptr);
        return NULL;
    }

    reg->table = reg_table[*ptr++];
    reg->offset = *ptr++;
    return ptr;
}