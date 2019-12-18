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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_decompressBegin (int /*<<< orphan*/ ) ; 
 size_t ZSTD_decompressContinue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t const) ; 
 size_t ZSTD_nextSrcSizeToDecompress (int /*<<< orphan*/ ) ; 
 int g_cSize ; 
 int /*<<< orphan*/  g_zdc ; 

__attribute__((used)) static size_t local_ZSTD_decompressContinue(const void* src, size_t srcSize,
                                            void* dst, size_t dstCapacity,
                                            void* buff2)
{
    size_t regeneratedSize = 0;
    const BYTE* ip = (const BYTE*)buff2;
    const BYTE* const iend = ip + g_cSize;
    BYTE* op = (BYTE*)dst;
    size_t remainingCapacity = dstCapacity;

    (void)src; (void)srcSize;  /* unused */
    ZSTD_decompressBegin(g_zdc);
    while (ip < iend) {
        size_t const iSize = ZSTD_nextSrcSizeToDecompress(g_zdc);
        size_t const decodedSize = ZSTD_decompressContinue(g_zdc, op, remainingCapacity, ip, iSize);
        ip += iSize;
        regeneratedSize += decodedSize;
        op += decodedSize;
        remainingCapacity -= decodedSize;
    }

    return regeneratedSize;
}