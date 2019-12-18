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
typedef  int /*<<< orphan*/  huffNodeTable ;
typedef  unsigned int U32 ;
typedef  scalar_t__ HUF_repeat ;
typedef  int /*<<< orphan*/  HUF_CElt ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_V_F (size_t const,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_count_wksp (unsigned int*,unsigned int*,int /*<<< orphan*/  const*,size_t,unsigned int*) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t HUF_BLOCKSIZE_MAX ; 
 int HUF_SYMBOLVALUE_MAX ; 
 unsigned int HUF_TABLELOG_DEFAULT ; 
 unsigned int HUF_TABLELOG_MAX ; 
 int /*<<< orphan*/  HUF_buildCTable_wksp (int /*<<< orphan*/ *,unsigned int*,unsigned int,unsigned int,void*,size_t) ; 
 size_t HUF_compressCTable_internal (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,void const*,size_t,unsigned int,int /*<<< orphan*/ *) ; 
 size_t HUF_estimateCompressedSize (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 unsigned int HUF_optimalTableLog (unsigned int,size_t,unsigned int) ; 
 scalar_t__ HUF_repeat_check ; 
 scalar_t__ HUF_repeat_none ; 
 scalar_t__ HUF_repeat_valid ; 
 int /*<<< orphan*/  HUF_validateCTable (int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  HUF_writeCTable_wksp (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,unsigned int,unsigned int,void*,size_t) ; 
 size_t const hSize ; 
 size_t largest ; 
 size_t const maxBits ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  srcSize_wrong ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

__attribute__((used)) static size_t HUF_compress_internal(void *dst, size_t dstSize, const void *src, size_t srcSize, unsigned maxSymbolValue, unsigned huffLog,
				    unsigned singleStream, void *workSpace, size_t wkspSize, HUF_CElt *oldHufTable, HUF_repeat *repeat, int preferRepeat)
{
	BYTE *const ostart = (BYTE *)dst;
	BYTE *const oend = ostart + dstSize;
	BYTE *op = ostart;

	U32 *count;
	size_t const countSize = sizeof(U32) * (HUF_SYMBOLVALUE_MAX + 1);
	HUF_CElt *CTable;
	size_t const CTableSize = sizeof(HUF_CElt) * (HUF_SYMBOLVALUE_MAX + 1);

	/* checks & inits */
	if (wkspSize < sizeof(huffNodeTable) + countSize + CTableSize)
		return ERROR(GENERIC);
	if (!srcSize)
		return 0; /* Uncompressed (note : 1 means rle, so first byte must be correct) */
	if (!dstSize)
		return 0; /* cannot fit within dst budget */
	if (srcSize > HUF_BLOCKSIZE_MAX)
		return ERROR(srcSize_wrong); /* curr block size limit */
	if (huffLog > HUF_TABLELOG_MAX)
		return ERROR(tableLog_tooLarge);
	if (!maxSymbolValue)
		maxSymbolValue = HUF_SYMBOLVALUE_MAX;
	if (!huffLog)
		huffLog = HUF_TABLELOG_DEFAULT;

	count = (U32 *)workSpace;
	workSpace = (BYTE *)workSpace + countSize;
	wkspSize -= countSize;
	CTable = (HUF_CElt *)workSpace;
	workSpace = (BYTE *)workSpace + CTableSize;
	wkspSize -= CTableSize;

	/* Heuristic : If we don't need to check the validity of the old table use the old table for small inputs */
	if (preferRepeat && repeat && *repeat == HUF_repeat_valid) {
		return HUF_compressCTable_internal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
	}

	/* Scan input and build symbol stats */
	{
		CHECK_V_F(largest, FSE_count_wksp(count, &maxSymbolValue, (const BYTE *)src, srcSize, (U32 *)workSpace));
		if (largest == srcSize) {
			*ostart = ((const BYTE *)src)[0];
			return 1;
		} /* single symbol, rle */
		if (largest <= (srcSize >> 7) + 1)
			return 0; /* Fast heuristic : not compressible enough */
	}

	/* Check validity of previous table */
	if (repeat && *repeat == HUF_repeat_check && !HUF_validateCTable(oldHufTable, count, maxSymbolValue)) {
		*repeat = HUF_repeat_none;
	}
	/* Heuristic : use existing table for small inputs */
	if (preferRepeat && repeat && *repeat != HUF_repeat_none) {
		return HUF_compressCTable_internal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
	}

	/* Build Huffman Tree */
	huffLog = HUF_optimalTableLog(huffLog, srcSize, maxSymbolValue);
	{
		CHECK_V_F(maxBits, HUF_buildCTable_wksp(CTable, count, maxSymbolValue, huffLog, workSpace, wkspSize));
		huffLog = (U32)maxBits;
		/* Zero the unused symbols so we can check it for validity */
		memset(CTable + maxSymbolValue + 1, 0, CTableSize - (maxSymbolValue + 1) * sizeof(HUF_CElt));
	}

	/* Write table description header */
	{
		CHECK_V_F(hSize, HUF_writeCTable_wksp(op, dstSize, CTable, maxSymbolValue, huffLog, workSpace, wkspSize));
		/* Check if using the previous table will be beneficial */
		if (repeat && *repeat != HUF_repeat_none) {
			size_t const oldSize = HUF_estimateCompressedSize(oldHufTable, count, maxSymbolValue);
			size_t const newSize = HUF_estimateCompressedSize(CTable, count, maxSymbolValue);
			if (oldSize <= hSize + newSize || hSize + 12 >= srcSize) {
				return HUF_compressCTable_internal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
			}
		}
		/* Use the new table */
		if (hSize + 12ul >= srcSize) {
			return 0;
		}
		op += hSize;
		if (repeat) {
			*repeat = HUF_repeat_none;
		}
		if (oldHufTable) {
			memcpy(oldHufTable, CTable, CTableSize);
		} /* Save the new table */
	}
	return HUF_compressCTable_internal(ostart, op, oend, src, srcSize, singleStream, CTable);
}