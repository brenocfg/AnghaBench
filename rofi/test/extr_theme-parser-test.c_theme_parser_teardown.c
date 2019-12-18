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
 int /*<<< orphan*/  ck_assert_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_assert_ptr_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  error_msg ; 
 int /*<<< orphan*/ * rofi_theme ; 
 int /*<<< orphan*/  rofi_theme_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void theme_parser_teardown ( void )
{
    ck_assert_ptr_null ( error_msg );
    ck_assert_int_eq ( error, 0);
    rofi_theme_free ( rofi_theme );
    rofi_theme = NULL;

}