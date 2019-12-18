#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ name; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_array (TYPE_1__*) ; 
 int /*<<< orphan*/  is_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (TYPE_1__*) ; 
 scalar_t__ type_is_alias (TYPE_1__*) ; 

int needs_space_after(type_t *t)
{
  return (type_is_alias(t) ||
          (!is_ptr(t) && (!is_array(t) || !type_array_is_decl_as_ptr(t) || t->name)));
}