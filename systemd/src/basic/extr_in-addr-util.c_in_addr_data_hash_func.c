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
struct siphash {int dummy; } ;
struct in_addr_data {int /*<<< orphan*/  family; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ *,int,struct siphash*) ; 

__attribute__((used)) static void in_addr_data_hash_func(const struct in_addr_data *a, struct siphash *state) {
        siphash24_compress(&a->family, sizeof(a->family), state);
        siphash24_compress(&a->address, FAMILY_ADDRESS_SIZE(a->family), state);
}