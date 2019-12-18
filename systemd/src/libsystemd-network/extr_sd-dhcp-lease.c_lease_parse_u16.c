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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  be16_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (scalar_t__ const*) ; 
 scalar_t__ unaligned_read_be16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lease_parse_u16(const uint8_t *option, size_t len, uint16_t *ret, uint16_t min) {
        assert(option);
        assert(ret);

        if (len != 2)
                return -EINVAL;

        *ret = unaligned_read_be16((be16_t*) option);
        if (*ret < min)
                *ret = min;

        return 0;
}