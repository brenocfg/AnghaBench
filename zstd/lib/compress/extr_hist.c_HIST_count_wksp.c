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
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t HIST_WKSP_SIZE ; 
 size_t HIST_countFast_wksp (unsigned int*,unsigned int*,void const*,size_t,void*,size_t) ; 
 size_t HIST_count_parallel_wksp (unsigned int*,unsigned int*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkMaxSymbolValue ; 
 int /*<<< orphan*/  workSpace_tooSmall ; 

size_t HIST_count_wksp(unsigned* count, unsigned* maxSymbolValuePtr,
                       const void* source, size_t sourceSize,
                       void* workSpace, size_t workSpaceSize)
{
    if ((size_t)workSpace & 3) return ERROR(GENERIC);  /* must be aligned on 4-bytes boundaries */
    if (workSpaceSize < HIST_WKSP_SIZE) return ERROR(workSpace_tooSmall);
    if (*maxSymbolValuePtr < 255)
        return HIST_count_parallel_wksp(count, maxSymbolValuePtr, source, sourceSize, checkMaxSymbolValue, (U32*)workSpace);
    *maxSymbolValuePtr = 255;
    return HIST_countFast_wksp(count, maxSymbolValuePtr, source, sourceSize, workSpace, workSpaceSize);
}