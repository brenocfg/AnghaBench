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
 int /*<<< orphan*/  DTable ; 
 int /*<<< orphan*/  HUF_CREATE_STATIC_DTABLEX1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUF_TABLELOG_MAX ; 
 size_t HUF_decompress4X1_DCtx (int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 

size_t HUF_decompress4X1 (void* dst, size_t dstSize, const void* cSrc, size_t cSrcSize)
{
    HUF_CREATE_STATIC_DTABLEX1(DTable, HUF_TABLELOG_MAX);
    return HUF_decompress4X1_DCtx(DTable, dst, dstSize, cSrc, cSrcSize);
}