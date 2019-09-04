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
 int /*<<< orphan*/  FSE_DEFAULT_TABLELOG ; 
 int /*<<< orphan*/  FSE_MAX_SYMBOL_VALUE ; 
 size_t FSE_compress2 (void*,size_t,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t FSE_compress (void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
    return FSE_compress2(dst, dstCapacity, src, srcSize, FSE_MAX_SYMBOL_VALUE, FSE_DEFAULT_TABLELOG);
}