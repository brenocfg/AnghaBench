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
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ var_t ;

/* Variables and functions */
 unsigned int ROUND_SIZE (unsigned int,int) ; 
 int /*<<< orphan*/  TDT_ALL_TYPES ; 
#define  TGT_BASIC 133 
#define  TGT_ENUM 132 
#define  TGT_RANGE 131 
#define  TGT_STRUCT 130 
#define  TGT_UNION 129 
#define  TGT_USER_TYPE 128 
 int pointer_size ; 
 unsigned int type_memsize (int /*<<< orphan*/ ) ; 
 int typegen_detect_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_stack_size( const var_t *var, int *by_value )
{
    unsigned int stack_size;
    int by_val;

    switch (typegen_detect_type( var->type, var->attrs, TDT_ALL_TYPES ))
    {
    case TGT_BASIC:
    case TGT_ENUM:
    case TGT_RANGE:
    case TGT_STRUCT:
    case TGT_UNION:
    case TGT_USER_TYPE:
        stack_size = type_memsize( var->type );
        by_val = (pointer_size < 8 || stack_size <= pointer_size); /* FIXME: should be platform-specific */
        break;
    default:
        by_val = 0;
        break;
    }
    if (!by_val) stack_size = pointer_size;
    if (by_value) *by_value = by_val;
    return ROUND_SIZE( stack_size, pointer_size );
}