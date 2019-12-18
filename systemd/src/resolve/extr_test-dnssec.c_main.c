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
 int /*<<< orphan*/  test_dnssec_canonicalize () ; 
 int /*<<< orphan*/  test_dnssec_nsec3_hash () ; 
 int /*<<< orphan*/  test_dnssec_verify_dns_key () ; 
 int /*<<< orphan*/  test_dnssec_verify_rfc8080_ed25519_example1 () ; 
 int /*<<< orphan*/  test_dnssec_verify_rfc8080_ed25519_example2 () ; 
 int /*<<< orphan*/  test_dnssec_verify_rrset () ; 
 int /*<<< orphan*/  test_dnssec_verify_rrset2 () ; 

int main(int argc, char *argv[]) {

        test_dnssec_canonicalize();

#if HAVE_GCRYPT
        test_dnssec_verify_dns_key();
        test_dnssec_verify_rfc8080_ed25519_example1();
        test_dnssec_verify_rfc8080_ed25519_example2();
        test_dnssec_verify_rrset();
        test_dnssec_verify_rrset2();
        test_dnssec_nsec3_hash();
#endif

        return 0;
}