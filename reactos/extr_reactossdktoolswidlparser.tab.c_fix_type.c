#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  structure; } ;
struct TYPE_10__ {int /*<<< orphan*/  defined; TYPE_1__ details; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 scalar_t__ TYPE_ENCAPSULATED_UNION ; 
 scalar_t__ TYPE_STRUCT ; 
 scalar_t__ TYPE_UNION ; 
 scalar_t__ is_incomplete (TYPE_2__*) ; 
 TYPE_2__* type_alias_get_aliasee (TYPE_2__*) ; 
 scalar_t__ type_get_type_detect_alias (TYPE_2__*) ; 
 scalar_t__ type_is_alias (TYPE_2__*) ; 

__attribute__((used)) static void fix_type(type_t *t)
{
  if (type_is_alias(t) && is_incomplete(t)) {
    type_t *ot = type_alias_get_aliasee(t);
    fix_type(ot);
    if (type_get_type_detect_alias(ot) == TYPE_STRUCT ||
        type_get_type_detect_alias(ot) == TYPE_UNION ||
        type_get_type_detect_alias(ot) == TYPE_ENCAPSULATED_UNION)
      t->details.structure = ot->details.structure;
    t->defined = ot->defined;
  }
}