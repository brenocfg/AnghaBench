#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtd ;
typedef  scalar_t__ U32 ;
struct TYPE_6__ {void* tableLog; scalar_t__ tableType; scalar_t__ maxTableLog; } ;
struct TYPE_5__ {void* nbBits; void* byte; } ;
typedef  int /*<<< orphan*/  HUFv07_DTable ;
typedef  TYPE_1__ HUFv07_DEltX2 ;
typedef  TYPE_2__ DTableDesc ;
typedef  void* BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv07_STATIC_ASSERT (int) ; 
 int HUFv07_SYMBOLVALUE_MAX ; 
 int /*<<< orphan*/  HUFv07_TABLELOG_ABSOLUTEMAX ; 
 TYPE_2__ HUFv07_getDTableDesc (int /*<<< orphan*/ *) ; 
 scalar_t__ HUFv07_isError (size_t) ; 
 size_t HUFv07_readStats (void**,int,scalar_t__*,scalar_t__*,scalar_t__*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t HUFv07_readDTableX2 (HUFv07_DTable* DTable, const void* src, size_t srcSize)
{
    BYTE huffWeight[HUFv07_SYMBOLVALUE_MAX + 1];
    U32 rankVal[HUFv07_TABLELOG_ABSOLUTEMAX + 1];   /* large enough for values from 0 to 16 */
    U32 tableLog = 0;
    U32 nbSymbols = 0;
    size_t iSize;
    void* const dtPtr = DTable + 1;
    HUFv07_DEltX2* const dt = (HUFv07_DEltX2*)dtPtr;

    HUFv07_STATIC_ASSERT(sizeof(DTableDesc) == sizeof(HUFv07_DTable));
    //memset(huffWeight, 0, sizeof(huffWeight));   /* is not necessary, even though some analyzer complain ... */

    iSize = HUFv07_readStats(huffWeight, HUFv07_SYMBOLVALUE_MAX + 1, rankVal, &nbSymbols, &tableLog, src, srcSize);
    if (HUFv07_isError(iSize)) return iSize;

    /* Table header */
    {   DTableDesc dtd = HUFv07_getDTableDesc(DTable);
        if (tableLog > (U32)(dtd.maxTableLog+1)) return ERROR(tableLog_tooLarge);   /* DTable too small, huffman tree cannot fit in */
        dtd.tableType = 0;
        dtd.tableLog = (BYTE)tableLog;
        memcpy(DTable, &dtd, sizeof(dtd));
    }

    /* Prepare ranks */
    {   U32 n, nextRankStart = 0;
        for (n=1; n<tableLog+1; n++) {
            U32 current = nextRankStart;
            nextRankStart += (rankVal[n] << (n-1));
            rankVal[n] = current;
    }   }

    /* fill DTable */
    {   U32 n;
        for (n=0; n<nbSymbols; n++) {
            U32 const w = huffWeight[n];
            U32 const length = (1 << w) >> 1;
            U32 i;
            HUFv07_DEltX2 D;
            D.byte = (BYTE)n; D.nbBits = (BYTE)(tableLog + 1 - w);
            for (i = rankVal[w]; i < rankVal[w] + length; i++)
                dt[i] = D;
            rankVal[w] += length;
    }   }

    return iSize;
}