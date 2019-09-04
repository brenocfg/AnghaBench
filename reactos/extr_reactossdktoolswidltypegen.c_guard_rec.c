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
struct TYPE_3__ {int typestring_offset; int /*<<< orphan*/  tfswrite; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static void guard_rec(type_t *type)
{
    /* types that contain references to themselves (like a linked list),
       need to be shielded from infinite recursion when writing embedded
       types  */
    if (type->typestring_offset)
        type->tfswrite = FALSE;
    else
        type->typestring_offset = 1;
}