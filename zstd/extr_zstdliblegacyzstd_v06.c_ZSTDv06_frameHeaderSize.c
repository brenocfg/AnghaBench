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
 size_t* ZSTDv06_fcs_fieldSize ; 
 size_t ZSTDv06_frameHeaderSize_min ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv06_frameHeaderSize(const void* src, size_t srcSize)
{
    if (srcSize < ZSTDv06_frameHeaderSize_min) return ERROR(srcSize_wrong);
    { U32 const fcsId = (((const BYTE*)src)[4]) >> 6;
      return ZSTDv06_frameHeaderSize_min + ZSTDv06_fcs_fieldSize[fcsId]; }
}