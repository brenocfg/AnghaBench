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
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t HUF_decompress1X4_usingDTable_internal (void*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ HUF_isError (size_t const) ; 
 size_t HUF_readDTableX4_wksp (int /*<<< orphan*/ *,void const*,size_t,void*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t HUF_decompress1X4_DCtx_wksp(HUF_DTable *DCtx, void *dst, size_t dstSize, const void *cSrc, size_t cSrcSize, void *workspace, size_t workspaceSize)
{
	const BYTE *ip = (const BYTE *)cSrc;

	size_t const hSize = HUF_readDTableX4_wksp(DCtx, cSrc, cSrcSize, workspace, workspaceSize);
	if (HUF_isError(hSize))
		return hSize;
	if (hSize >= cSrcSize)
		return ERROR(srcSize_wrong);
	ip += hSize;
	cSrcSize -= hSize;

	return HUF_decompress1X4_usingDTable_internal(dst, dstSize, ip, cSrcSize, DCtx);
}