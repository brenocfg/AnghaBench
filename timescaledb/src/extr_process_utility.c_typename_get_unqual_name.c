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
struct TYPE_6__ {char const* str; } ;
struct TYPE_7__ {TYPE_1__ val; } ;
typedef  TYPE_2__ Value ;
struct TYPE_8__ {int /*<<< orphan*/  names; } ;
typedef  TYPE_3__ TypeName ;

/* Variables and functions */
 TYPE_2__* llast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *
typename_get_unqual_name(TypeName *tn)
{
	Value *name = llast(tn->names);

	return name->val.str;
}