#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  cParams; TYPE_2__ fParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;
typedef  TYPE_2__ ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,int /*<<< orphan*/ ) ; 
 int FIRST_BLOCK_SIZE ; 
 int /*<<< orphan*/  ZSTD_compressBegin_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__,size_t) ; 
 size_t ZSTD_compressContinue (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,int) ; 
 size_t ZSTD_compressEnd (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  g_zcc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static size_t
local_ZSTD_compressContinue_extDict(const void* src, size_t srcSize,
                                    void* dst, size_t dstCapacity,
                                    void* payload)
{
    BYTE firstBlockBuf[FIRST_BLOCK_SIZE];

    ZSTD_parameters p;
    ZSTD_frameParameters const f = { 1, 0, 0 };
    p.fParams = f;
    p.cParams = *(ZSTD_compressionParameters*)payload;
    ZSTD_compressBegin_advanced(g_zcc, NULL, 0, p, srcSize);
    memcpy(firstBlockBuf, src, FIRST_BLOCK_SIZE);

    {   size_t const compressResult = ZSTD_compressContinue(g_zcc,
                                            dst, dstCapacity,
                                            firstBlockBuf, FIRST_BLOCK_SIZE);
        if (ZSTD_isError(compressResult)) {
            DISPLAY("local_ZSTD_compressContinue_extDict error : %s\n",
                    ZSTD_getErrorName(compressResult));
            return compressResult;
        }
        dst = (BYTE*)dst + compressResult;
        dstCapacity -= compressResult;
    }
    return ZSTD_compressEnd(g_zcc, dst, dstCapacity,
                            (const BYTE*)src + FIRST_BLOCK_SIZE,
                            srcSize - FIRST_BLOCK_SIZE);
}