#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; scalar_t__ sign; } ;
struct TYPE_7__ {TYPE_1__ basic; } ;
struct TYPE_8__ {TYPE_2__ details; } ;
typedef  TYPE_3__ type_t ;
typedef  enum type_basic_type { ____Placeholder_type_basic_type } type_basic_type ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_BASIC ; 
 TYPE_3__* make_type (int /*<<< orphan*/ ) ; 

type_t *type_new_basic(enum type_basic_type basic_type)
{
    type_t *t = make_type(TYPE_BASIC);
    t->details.basic.type = basic_type;
    t->details.basic.sign = 0;
    return t;
}