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
typedef  unsigned int U32 ;
typedef  unsigned int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 

unsigned HIST_count_simple(unsigned* count, unsigned* maxSymbolValuePtr,
                           const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    const BYTE* const end = ip + srcSize;
    unsigned maxSymbolValue = *maxSymbolValuePtr;
    unsigned largestCount=0;

    memset(count, 0, (maxSymbolValue+1) * sizeof(*count));
    if (srcSize==0) { *maxSymbolValuePtr = 0; return 0; }

    while (ip<end) {
        assert(*ip <= maxSymbolValue);
        count[*ip++]++;
    }

    while (!count[maxSymbolValue]) maxSymbolValue--;
    *maxSymbolValuePtr = maxSymbolValue;

    {   U32 s;
        for (s=0; s<=maxSymbolValue; s++)
            if (count[s] > largestCount) largestCount = count[s];
    }

    return largestCount;
}