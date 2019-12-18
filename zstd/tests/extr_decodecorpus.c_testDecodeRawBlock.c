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
struct TYPE_3__ {scalar_t__ srcStart; scalar_t__ src; scalar_t__ dataStart; scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DECOMPRESSED_BUFFER ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_DECOMPRESSED_SIZE ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 size_t ZSTD_decompressBegin (int /*<<< orphan*/ *) ; 
 size_t ZSTD_decompressBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static size_t testDecodeRawBlock(frame_t* fr)
{
    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    size_t ret = ZSTD_decompressBegin(dctx);
    if (ZSTD_isError(ret)) return ret;

    ret = ZSTD_decompressBlock(
            dctx,
            DECOMPRESSED_BUFFER, MAX_DECOMPRESSED_SIZE,
            fr->dataStart, (BYTE*)fr->data - (BYTE*)fr->dataStart);
    ZSTD_freeDCtx(dctx);
    if (ZSTD_isError(ret)) return ret;

    if (memcmp(DECOMPRESSED_BUFFER, fr->srcStart,
               (BYTE*)fr->src - (BYTE*)fr->srcStart) != 0) {
        return ERROR(corruption_detected);
    }

    return ret;
}