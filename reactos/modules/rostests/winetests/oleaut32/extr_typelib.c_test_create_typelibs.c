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

/* Variables and functions */
 int LOCALE_NEUTRAL ; 
 int LOCALE_SYSTEM_DEFAULT ; 
 int LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  test_create_typelib_lcid (int) ; 

__attribute__((used)) static void test_create_typelibs(void)
{
    test_create_typelib_lcid(LOCALE_SYSTEM_DEFAULT);
    test_create_typelib_lcid(LOCALE_USER_DEFAULT);
    test_create_typelib_lcid(LOCALE_NEUTRAL);

    test_create_typelib_lcid(0x009);
    test_create_typelib_lcid(0x409);
    test_create_typelib_lcid(0x809);

    test_create_typelib_lcid(0x007);
    test_create_typelib_lcid(0x407);
}