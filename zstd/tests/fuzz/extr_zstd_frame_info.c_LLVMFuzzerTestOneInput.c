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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ZSTD_frameHeader ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_decompressBound (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_f_zstd1 ; 
 int /*<<< orphan*/  ZSTD_findDecompressedSize (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_findFrameCompressedSize (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_frameHeaderSize (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getDecompressedSize (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getDictID_fromFrame (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getFrameContentSize (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getFrameHeader (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getFrameHeader_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_isFrame (int /*<<< orphan*/  const*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    ZSTD_frameHeader zfh;
    /* You can fuzz any helper functions here that are fast, and take zstd
     * compressed data as input. E.g. don't expect the input to be a dictionary,
     * so don't fuzz ZSTD_getDictID_fromDict().
     */
    ZSTD_getFrameContentSize(src, size);
    ZSTD_getDecompressedSize(src, size);
    ZSTD_findFrameCompressedSize(src, size);
    ZSTD_getDictID_fromFrame(src, size);
    ZSTD_findDecompressedSize(src, size);
    ZSTD_decompressBound(src, size);
    ZSTD_frameHeaderSize(src, size);
    ZSTD_isFrame(src, size);
    ZSTD_getFrameHeader(&zfh, src, size);
    ZSTD_getFrameHeader_advanced(&zfh, src, size, ZSTD_f_zstd1);
    return 0;
}