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

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t const) ; 

__attribute__((used)) static size_t ZSTD_limitCopy(void* dst, size_t dstCapacity,
                       const void* src, size_t srcSize)
{
    size_t const length = MIN(dstCapacity, srcSize);
    if (length) memcpy(dst, src, length);
    return length;
}