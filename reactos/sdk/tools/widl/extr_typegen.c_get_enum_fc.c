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
 int /*<<< orphan*/  ATTR_V1ENUM ; 
 unsigned char FC_ENUM16 ; 
 unsigned char FC_ENUM32 ; 
 scalar_t__ TYPE_ENUM ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_aliaschain_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ type_get_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned char get_enum_fc(const type_t *type)
{
    assert(type_get_type(type) == TYPE_ENUM);
    if (is_aliaschain_attr(type, ATTR_V1ENUM))
        return FC_ENUM32;
    else
        return FC_ENUM16;
}