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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void uint64_export(void *buf, size_t buflen, uint64_t x) {
        assert(buflen == 8);
        ((uint8_t*) buf)[0] = (x >> 56) & 0xff;
        ((uint8_t*) buf)[1] = (x >> 48) & 0xff;
        ((uint8_t*) buf)[2] = (x >> 40) & 0xff;
        ((uint8_t*) buf)[3] = (x >> 32) & 0xff;
        ((uint8_t*) buf)[4] = (x >> 24) & 0xff;
        ((uint8_t*) buf)[5] = (x >> 16) & 0xff;
        ((uint8_t*) buf)[6] = (x >>  8) & 0xff;
        ((uint8_t*) buf)[7] = (x >>  0) & 0xff;
}