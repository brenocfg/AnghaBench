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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int TRUE ; 
 scalar_t__ TYPE_ARRAY ; 
 scalar_t__ TYPE_BASIC ; 
 scalar_t__ TYPE_ENUM ; 
 scalar_t__ TYPE_POINTER ; 
 scalar_t__ is_user_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ type_get_type (int /*<<< orphan*/  const*) ; 

int decl_indirect(const type_t *t)
{
    if (is_user_type(t))
        return TRUE;
    return (type_get_type(t) != TYPE_BASIC &&
            type_get_type(t) != TYPE_ENUM &&
            type_get_type(t) != TYPE_POINTER &&
            type_get_type(t) != TYPE_ARRAY);
}