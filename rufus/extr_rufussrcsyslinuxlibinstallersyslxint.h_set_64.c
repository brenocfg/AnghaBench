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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void set_64(uint64_t *p, uint64_t v)
{
#if X86_MEM
    /* Littleendian and unaligned-capable */
    *p = v;
#else
    uint32_t *pp = (uint32_t *) p;
    set_32(&pp[0], v);
    set_32(&pp[1], v >> 32);
#endif
}