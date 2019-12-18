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
 int /*<<< orphan*/  test_base32hexchar () ; 
 int /*<<< orphan*/  test_base32hexmem () ; 
 int /*<<< orphan*/  test_base64char () ; 
 int /*<<< orphan*/  test_base64mem () ; 
 int /*<<< orphan*/  test_decchar () ; 
 int /*<<< orphan*/  test_hexchar () ; 
 int /*<<< orphan*/  test_hexdump () ; 
 int /*<<< orphan*/  test_octchar () ; 
 int /*<<< orphan*/  test_unbase32hexchar () ; 
 int /*<<< orphan*/  test_unbase32hexmem () ; 
 int /*<<< orphan*/  test_unbase64char () ; 
 int /*<<< orphan*/  test_unbase64mem () ; 
 int /*<<< orphan*/  test_undecchar () ; 
 int /*<<< orphan*/  test_unhexchar () ; 
 int /*<<< orphan*/  test_unhexmem () ; 
 int /*<<< orphan*/  test_unoctchar () ; 

int main(int argc, char *argv[]) {
        test_hexchar();
        test_unhexchar();
        test_base32hexchar();
        test_unbase32hexchar();
        test_base64char();
        test_unbase64char();
        test_octchar();
        test_unoctchar();
        test_decchar();
        test_undecchar();
        test_unhexmem();
        test_base32hexmem();
        test_unbase32hexmem();
        test_base64mem();
        test_unbase64mem();
        test_hexdump();

        return 0;
}