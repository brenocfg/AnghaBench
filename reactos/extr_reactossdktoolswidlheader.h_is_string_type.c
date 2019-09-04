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
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_STRING ; 
 scalar_t__ is_aliaschain_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ last_array (int /*<<< orphan*/  const*) ; 
 scalar_t__ last_ptr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int is_string_type(const attr_list_t *attrs, const type_t *type)
{
    return ((is_attr(attrs, ATTR_STRING) || is_aliaschain_attr(type, ATTR_STRING))
            && (last_ptr(type) || last_array(type)));
}