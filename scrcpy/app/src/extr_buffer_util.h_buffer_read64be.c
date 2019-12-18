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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int buffer_read32be (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline
uint64_t buffer_read64be(const uint8_t *buf) {
    uint32_t msb = buffer_read32be(buf);
    uint32_t lsb = buffer_read32be(&buf[4]);
    return ((uint64_t) msb << 32) | lsb;
}