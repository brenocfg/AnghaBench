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
struct in_addr_data {int /*<<< orphan*/  family; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in_addr_data_compare_func(const struct in_addr_data *x, const struct in_addr_data *y) {
        int r;

        r = CMP(x->family, y->family);
        if (r != 0)
                return r;

        return memcmp(&x->address, &y->address, FAMILY_ADDRESS_SIZE(x->family));
}