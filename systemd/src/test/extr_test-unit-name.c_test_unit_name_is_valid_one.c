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
typedef  int UnitNameFlags ;

/* Variables and functions */
 int UNIT_NAME_INSTANCE ; 
 int UNIT_NAME_PLAIN ; 
 int UNIT_NAME_TEMPLATE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,char const*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int unit_name_is_valid (char const*,int) ; 
 int /*<<< orphan*/  yes_no (int) ; 

__attribute__((used)) static void test_unit_name_is_valid_one(const char *name, UnitNameFlags flags, bool expected) {
        log_info("%s ( %s%s%s ): %s",
                 name,
                 (flags & UNIT_NAME_PLAIN) ? "plain" : "",
                 (flags & UNIT_NAME_INSTANCE) ? " instance" : "",
                 (flags & UNIT_NAME_TEMPLATE) ? " template" : "",
                 yes_no(expected));
        assert_se(unit_name_is_valid(name, flags) == expected);
}