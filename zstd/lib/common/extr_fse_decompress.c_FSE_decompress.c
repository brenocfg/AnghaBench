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
typedef  int /*<<< orphan*/  DTable_max_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_MAX_TABLELOG ; 
 size_t FSE_decompress_wksp (void*,size_t,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t FSE_decompress(void* dst, size_t dstCapacity, const void* cSrc, size_t cSrcSize)
{
    DTable_max_t dt;   /* Static analyzer seems unable to understand this table will be properly initialized later */
    return FSE_decompress_wksp(dst, dstCapacity, cSrc, cSrcSize, dt, FSE_MAX_TABLELOG);
}