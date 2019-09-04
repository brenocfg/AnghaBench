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
 int /*<<< orphan*/  test_pack_ASSOCF () ; 
 int /*<<< orphan*/  test_pack_DLLGETVERSIONPROC () ; 
 int /*<<< orphan*/  test_pack_DLLVERSIONINFO () ; 
 int /*<<< orphan*/  test_pack_DLLVERSIONINFO2 () ; 
 int /*<<< orphan*/  test_pack_HUSKEY () ; 
 int /*<<< orphan*/  test_pack_PHUSKEY () ; 

__attribute__((used)) static void test_pack(void)
{
    test_pack_ASSOCF();
    test_pack_DLLGETVERSIONPROC();
    test_pack_DLLVERSIONINFO();
    test_pack_DLLVERSIONINFO2();
    test_pack_HUSKEY();
    test_pack_PHUSKEY();
}