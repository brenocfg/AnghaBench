#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct siphash {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  dns_name_hash_func (int /*<<< orphan*/ ,struct siphash*) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ *,int,struct siphash*) ; 

__attribute__((used)) static void dns_resource_key_hash_func(const DnsResourceKey *k, struct siphash *state) {
        assert(k);

        dns_name_hash_func(dns_resource_key_name(k), state);
        siphash24_compress(&k->class, sizeof(k->class), state);
        siphash24_compress(&k->type, sizeof(k->type), state);
}