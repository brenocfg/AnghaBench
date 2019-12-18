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
struct TYPE_5__ {int size; } ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int* DNS_PACKET_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 

__attribute__((used)) static void dns_packet_hash_func(const DnsPacket *s, struct siphash *state) {
        assert(s);

        siphash24_compress(&s->size, sizeof(s->size), state);
        siphash24_compress(DNS_PACKET_DATA((DnsPacket*) s), s->size, state);
}