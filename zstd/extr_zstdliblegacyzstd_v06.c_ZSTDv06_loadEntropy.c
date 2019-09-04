#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flagRepeatTable; int /*<<< orphan*/  LLTable; int /*<<< orphan*/  MLTable; int /*<<< orphan*/  OffTable; int /*<<< orphan*/  hufTableX4; } ;
typedef  TYPE_1__ ZSTDv06_DCtx ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t FSEv06_buildDTable (int /*<<< orphan*/ ,short*,unsigned int,unsigned int) ; 
 scalar_t__ FSEv06_isError (size_t const) ; 
 size_t FSEv06_readNCount (short*,...) ; 
 scalar_t__ HUFv06_isError (size_t) ; 
 size_t HUFv06_readDTableX4 (int /*<<< orphan*/ ,void const*,size_t) ; 
 unsigned int LLFSELog ; 
 unsigned int MLFSELog ; 
 int MaxLL ; 
 int MaxML ; 
 scalar_t__ MaxOff ; 
 scalar_t__ OffFSELog ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

__attribute__((used)) static size_t ZSTDv06_loadEntropy(ZSTDv06_DCtx* dctx, const void* dict, size_t dictSize)
{
    size_t hSize, offcodeHeaderSize, matchlengthHeaderSize, litlengthHeaderSize;

    hSize = HUFv06_readDTableX4(dctx->hufTableX4, dict, dictSize);
    if (HUFv06_isError(hSize)) return ERROR(dictionary_corrupted);
    dict = (const char*)dict + hSize;
    dictSize -= hSize;

    {   short offcodeNCount[MaxOff+1];
        U32 offcodeMaxValue=MaxOff, offcodeLog;
        offcodeHeaderSize = FSEv06_readNCount(offcodeNCount, &offcodeMaxValue, &offcodeLog, dict, dictSize);
        if (FSEv06_isError(offcodeHeaderSize)) return ERROR(dictionary_corrupted);
        if (offcodeLog > OffFSELog) return ERROR(dictionary_corrupted);
        { size_t const errorCode = FSEv06_buildDTable(dctx->OffTable, offcodeNCount, offcodeMaxValue, offcodeLog);
          if (FSEv06_isError(errorCode)) return ERROR(dictionary_corrupted); }
        dict = (const char*)dict + offcodeHeaderSize;
        dictSize -= offcodeHeaderSize;
    }

    {   short matchlengthNCount[MaxML+1];
        unsigned matchlengthMaxValue = MaxML, matchlengthLog;
        matchlengthHeaderSize = FSEv06_readNCount(matchlengthNCount, &matchlengthMaxValue, &matchlengthLog, dict, dictSize);
        if (FSEv06_isError(matchlengthHeaderSize)) return ERROR(dictionary_corrupted);
        if (matchlengthLog > MLFSELog) return ERROR(dictionary_corrupted);
        { size_t const errorCode = FSEv06_buildDTable(dctx->MLTable, matchlengthNCount, matchlengthMaxValue, matchlengthLog);
          if (FSEv06_isError(errorCode)) return ERROR(dictionary_corrupted); }
        dict = (const char*)dict + matchlengthHeaderSize;
        dictSize -= matchlengthHeaderSize;
    }

    {   short litlengthNCount[MaxLL+1];
        unsigned litlengthMaxValue = MaxLL, litlengthLog;
        litlengthHeaderSize = FSEv06_readNCount(litlengthNCount, &litlengthMaxValue, &litlengthLog, dict, dictSize);
        if (FSEv06_isError(litlengthHeaderSize)) return ERROR(dictionary_corrupted);
        if (litlengthLog > LLFSELog) return ERROR(dictionary_corrupted);
        { size_t const errorCode = FSEv06_buildDTable(dctx->LLTable, litlengthNCount, litlengthMaxValue, litlengthLog);
          if (FSEv06_isError(errorCode)) return ERROR(dictionary_corrupted); }
    }

    dctx->flagRepeatTable = 1;
    return hSize + offcodeHeaderSize + matchlengthHeaderSize + litlengthHeaderSize;
}