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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  test_is_fido_security_token_desc__fido () ; 
 int /*<<< orphan*/  test_is_fido_security_token_desc__invalid () ; 
 int /*<<< orphan*/  test_is_fido_security_token_desc__non_fido () ; 

int main(int argc, char *argv[]) {
        test_is_fido_security_token_desc__fido();
        test_is_fido_security_token_desc__non_fido();
        test_is_fido_security_token_desc__invalid();

        return EXIT_SUCCESS;
}