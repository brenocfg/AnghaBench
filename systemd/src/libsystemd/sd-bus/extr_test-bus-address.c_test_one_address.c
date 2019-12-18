#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * address; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int bus_set_address_system_remote (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_one_address(sd_bus *b,
                             const char *host,
                             int result, const char *expected) {
        int r;

        r = bus_set_address_system_remote(b, host);
        log_info("\"%s\" → %d, \"%s\"", host, r, strna(r >= 0 ? b->address : NULL));
        if (result < 0 || expected) {
                assert(r == result);
                if (r >= 0)
                        assert_se(streq(b->address, expected));
        }
}