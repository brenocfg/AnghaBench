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
 int /*<<< orphan*/  HUFv07_CREATE_STATIC_DTABLEX2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv07_TABLELOG_MAX ; 
 size_t HUFv07_decompress1X2_DCtx (int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 

size_t HUFv07_decompress1X2 (void* dst, size_t dstSize, const void* cSrc, size_t cSrcSize)
{
    HUFv07_CREATE_STATIC_DTABLEX2(DTable, HUFv07_TABLELOG_MAX);
    return HUFv07_decompress1X2_DCtx (DTable, dst, dstSize, cSrc, cSrcSize);
}