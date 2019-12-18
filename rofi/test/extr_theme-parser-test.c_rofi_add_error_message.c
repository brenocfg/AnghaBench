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
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ck_assert_ptr_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/ * error_msg ; 

void rofi_add_error_message ( GString *msg )
{
    ck_assert_ptr_null ( error_msg );
    error_msg = msg;
    error = TRUE;
}