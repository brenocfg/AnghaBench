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
typedef  int const uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int const get_16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline uint32_t get_32(const uint32_t * p)
{
#if X86_MEM
    /* Littleendian and unaligned-capable */
    return *p;
#else
    const uint16_t *pp = (const uint16_t *)p;
    return get_16(&pp[0]) + ((uint32_t)get_16(&pp[1]) << 16);
#endif
}