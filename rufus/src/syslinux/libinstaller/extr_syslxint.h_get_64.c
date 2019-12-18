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
typedef  int const uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int const get_32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline uint64_t get_64(const uint64_t * p)
{
#if X86_MEM
    /* Littleendian and unaligned-capable */
    return *p;
#else
    const uint32_t *pp = (const uint32_t *)p;
    return get_32(&pp[0]) + ((uint64_t)get_32(&pp[1]) << 32);
#endif
}