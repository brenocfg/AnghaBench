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
typedef  int /*<<< orphan*/  ZSTD_DDict ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int U32 ;
typedef  void BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 void* ZSTD_DDictDictContent (int /*<<< orphan*/  const*) ; 
 size_t ZSTD_DDictDictSize (int /*<<< orphan*/  const*) ; 
 int ZSTD_MAGICNUMBER ; 
 int ZSTD_MAGIC_SKIPPABLE_START ; 
 int /*<<< orphan*/  ZSTD_checkContinuity (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin_usingDict (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTD_decompressFrame (int /*<<< orphan*/ *,void*,size_t,void const**,size_t*) ; 
 size_t ZSTD_frameHeaderSize_prefix ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t ZSTD_readLE32 (void const*) ; 
 int /*<<< orphan*/  ZSTD_refDDict (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 size_t ZSTD_skippableHeaderSize ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_decompressMultiFrame(ZSTD_DCtx *dctx, void *dst, size_t dstCapacity, const void *src, size_t srcSize, const void *dict, size_t dictSize,
					const ZSTD_DDict *ddict)
{
	void *const dststart = dst;

	if (ddict) {
		if (dict) {
			/* programmer error, these two cases should be mutually exclusive */
			return ERROR(GENERIC);
		}

		dict = ZSTD_DDictDictContent(ddict);
		dictSize = ZSTD_DDictDictSize(ddict);
	}

	while (srcSize >= ZSTD_frameHeaderSize_prefix) {
		U32 magicNumber;

		magicNumber = ZSTD_readLE32(src);
		if (magicNumber != ZSTD_MAGICNUMBER) {
			if ((magicNumber & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) {
				size_t skippableSize;
				if (srcSize < ZSTD_skippableHeaderSize)
					return ERROR(srcSize_wrong);
				skippableSize = ZSTD_readLE32((const BYTE *)src + 4) + ZSTD_skippableHeaderSize;
				if (srcSize < skippableSize) {
					return ERROR(srcSize_wrong);
				}

				src = (const BYTE *)src + skippableSize;
				srcSize -= skippableSize;
				continue;
			} else {
				return ERROR(prefix_unknown);
			}
		}

		if (ddict) {
			/* we were called from ZSTD_decompress_usingDDict */
			ZSTD_refDDict(dctx, ddict);
		} else {
			/* this will initialize correctly with no dict if dict == NULL, so
			 * use this in all cases but ddict */
			CHECK_F(ZSTD_decompressBegin_usingDict(dctx, dict, dictSize));
		}
		ZSTD_checkContinuity(dctx, dst);

		{
			const size_t res = ZSTD_decompressFrame(dctx, dst, dstCapacity, &src, &srcSize);
			if (ZSTD_isError(res))
				return res;
			/* don't need to bounds check this, ZSTD_decompressFrame will have
			 * already */
			dst = (BYTE *)dst + res;
			dstCapacity -= res;
		}
	}

	if (srcSize)
		return ERROR(srcSize_wrong); /* input not entirely consumed */

	return (BYTE *)dst - (BYTE *)dststart;
}