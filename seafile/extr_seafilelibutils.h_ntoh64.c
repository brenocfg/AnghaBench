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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bswap64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t 
ntoh64(uint64_t val) 
{
#if __BYTE_ORDER == __LITTLE_ENDIAN || defined WIN32 || defined __APPLE__
    return bswap64 (val);
#else
    return val;
#endif
}