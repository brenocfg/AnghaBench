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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 scalar_t__ XXH_CPU_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  XXH_read32 (void const*) ; 
 int /*<<< orphan*/  XXH_swap32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static U32 XXH_readBE32(const void* ptr)
{
    return XXH_CPU_LITTLE_ENDIAN ? XXH_swap32(XXH_read32(ptr)) : XXH_read32(ptr);
}