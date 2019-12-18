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
struct TYPE_3__ {int type_type; scalar_t__ is_alias; } ;
typedef  TYPE_1__ type_t ;
typedef  enum type_type { ____Placeholder_type_type } type_type ;

/* Variables and functions */
 int TYPE_ALIAS ; 

__attribute__((used)) static inline enum type_type type_get_type_detect_alias(const type_t *type)
{
    if (type->is_alias)
        return TYPE_ALIAS;
    return type->type_type;
}