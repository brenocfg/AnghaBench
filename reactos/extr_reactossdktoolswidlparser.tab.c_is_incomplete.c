#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defined; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 scalar_t__ TYPE_ENCAPSULATED_UNION ; 
 scalar_t__ TYPE_STRUCT ; 
 scalar_t__ TYPE_UNION ; 
 scalar_t__ type_get_type_detect_alias (TYPE_1__ const*) ; 

__attribute__((used)) static int is_incomplete(const type_t *t)
{
  return !t->defined &&
    (type_get_type_detect_alias(t) == TYPE_STRUCT ||
     type_get_type_detect_alias(t) == TYPE_UNION ||
     type_get_type_detect_alias(t) == TYPE_ENCAPSULATED_UNION);
}