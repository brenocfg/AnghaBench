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
typedef  int uint8_t ;
typedef  unsigned char in_addr ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  assert (unsigned char const*) ; 

int in4_addr_default_prefixlen(const struct in_addr *addr, unsigned char *prefixlen) {
        uint8_t msb_octet = *(uint8_t*) addr;

        /* addr may not be aligned, so make sure we only access it byte-wise */

        assert(addr);
        assert(prefixlen);

        if (msb_octet < 128)
                /* class A, leading bits: 0 */
                *prefixlen = 8;
        else if (msb_octet < 192)
                /* class B, leading bits 10 */
                *prefixlen = 16;
        else if (msb_octet < 224)
                /* class C, leading bits 110 */
                *prefixlen = 24;
        else
                /* class D or E, no default prefixlen */
                return -ERANGE;

        return 0;
}