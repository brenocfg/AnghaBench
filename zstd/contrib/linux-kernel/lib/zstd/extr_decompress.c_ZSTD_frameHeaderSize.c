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
typedef  size_t U32 ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t* ZSTD_did_fieldSize ; 
 size_t* ZSTD_fcs_fieldSize ; 
 size_t ZSTD_frameHeaderSize_prefix ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_frameHeaderSize(const void *src, size_t srcSize)
{
	if (srcSize < ZSTD_frameHeaderSize_prefix)
		return ERROR(srcSize_wrong);
	{
		BYTE const fhd = ((const BYTE *)src)[4];
		U32 const dictID = fhd & 3;
		U32 const singleSegment = (fhd >> 5) & 1;
		U32 const fcsId = fhd >> 6;
		return ZSTD_frameHeaderSize_prefix + !singleSegment + ZSTD_did_fieldSize[dictID] + ZSTD_fcs_fieldSize[fcsId] + (singleSegment && !fcsId);
	}
}