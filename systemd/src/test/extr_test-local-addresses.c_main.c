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
struct local_address {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free (struct local_address*) ; 
 int local_addresses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct local_address**) ; 
 int local_gateways (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct local_address**) ; 
 struct local_address* mfree (struct local_address*) ; 
 int /*<<< orphan*/  print_local_addresses (struct local_address*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        struct local_address *a;
        int n;

        test_setup_logging(LOG_DEBUG);

        a = NULL;
        n = local_addresses(NULL, 0, AF_UNSPEC, &a);
        assert_se(n >= 0);

        printf("Local Addresses:\n");
        print_local_addresses(a, (unsigned) n);
        a = mfree(a);

        n = local_gateways(NULL, 0, AF_UNSPEC, &a);
        assert_se(n >= 0);

        printf("Local Gateways:\n");
        print_local_addresses(a, (unsigned) n);
        free(a);

        return 0;
}