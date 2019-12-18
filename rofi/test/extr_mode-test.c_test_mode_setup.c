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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ck_assert_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_keys_mode ; 
 int /*<<< orphan*/  mode_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_mode_setup ( void )
{
    ck_assert_int_eq ( mode_init ( &help_keys_mode ), TRUE);
}