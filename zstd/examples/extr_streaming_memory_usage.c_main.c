#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decompressedData ;
typedef  int /*<<< orphan*/  dataToCompress ;
typedef  int /*<<< orphan*/  compressedData ;
struct TYPE_8__ {char* member_0; int member_1; size_t pos; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_9__ {char const* member_0; int member_1; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,...) ; 
 int /*<<< orphan*/  CHECK_ZSTD (size_t const) ; 
 int COMPRESSED_SIZE ; 
 int INPUT_SIZE ; 
 int MAX_TESTED_LEVEL ; 
 size_t const ZSTD_CCtxParams_setParameter (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,unsigned int) ; 
 size_t const ZSTD_CCtx_setParametersUsingCCtxParams (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 size_t const ZSTD_DCtx_setParameter (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ZSTD_c_compressionLevel ; 
 int /*<<< orphan*/  ZSTD_c_windowLog ; 
 size_t const ZSTD_compressStream (int /*<<< orphan*/ * const,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createCCtxParams () ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 int /*<<< orphan*/  ZSTD_d_windowLogMax ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ * const,TYPE_1__*,TYPE_2__*) ; 
 size_t ZSTD_endStream (int /*<<< orphan*/ * const,TYPE_1__*) ; 
 size_t ZSTD_estimateCStreamSize_usingCCtxParams (int /*<<< orphan*/ * const) ; 
 size_t ZSTD_estimateDStreamSize_fromFrame (char*,size_t) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_freeCCtxParams (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ * const) ; 
 size_t ZSTD_sizeof_CStream (int /*<<< orphan*/ * const) ; 
 size_t ZSTD_sizeof_DStream (int /*<<< orphan*/ * const) ; 
 char* ZSTD_versionString () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned int readU32FromChar (char const**) ; 

int main(int argc, char const *argv[]) {

    printf("\n Zstandard (v%s) memory usage for streaming : \n\n", ZSTD_versionString());

    unsigned wLog = 0;
    if (argc > 1) {
        const char* valStr = argv[1];
        wLog = readU32FromChar(&valStr);
    }

    int compressionLevel;
    for (compressionLevel = 1; compressionLevel <= MAX_TESTED_LEVEL; compressionLevel++) {
#define INPUT_SIZE 5
#define COMPRESSED_SIZE 128
        char const dataToCompress[INPUT_SIZE] = "abcde";
        char compressedData[COMPRESSED_SIZE];
        char decompressedData[INPUT_SIZE];
        /* the ZSTD_CCtx_params structure is a way to save parameters and use
         * them across multiple contexts. We use them here so we can call the
         * function ZSTD_estimateCStreamSize_usingCCtxParams().
         */
        ZSTD_CCtx_params* const cctxParams = ZSTD_createCCtxParams();
        CHECK(cctxParams != NULL, "ZSTD_createCCtxParams() failed!");

        /* Set the compression level. */
        CHECK_ZSTD( ZSTD_CCtxParams_setParameter(cctxParams, ZSTD_c_compressionLevel, compressionLevel) );
        /* Set the window log.
         * The value 0 means use the default window log, which is equivalent to
         * not setting it.
         */
        CHECK_ZSTD( ZSTD_CCtxParams_setParameter(cctxParams, ZSTD_c_windowLog, wLog) );

        /* Force the compressor to allocate the maximum memory size for a given
         * level by not providing the pledged source size, or calling
         * ZSTD_compressStream2() with ZSTD_e_end.
         */
        ZSTD_CCtx* const cctx = ZSTD_createCCtx();
        CHECK(cctx != NULL, "ZSTD_createCCtx() failed!");
        CHECK_ZSTD( ZSTD_CCtx_setParametersUsingCCtxParams(cctx, cctxParams) );
        size_t compressedSize;
        {
            ZSTD_inBuffer inBuff = { dataToCompress, sizeof(dataToCompress), 0 };
            ZSTD_outBuffer outBuff = { compressedData, sizeof(compressedData), 0 };
            CHECK_ZSTD( ZSTD_compressStream(cctx, &outBuff, &inBuff) );
            size_t const remaining = ZSTD_endStream(cctx, &outBuff);
            CHECK_ZSTD(remaining);
            CHECK(remaining == 0, "Frame not flushed!");
            compressedSize = outBuff.pos;
        }

        ZSTD_DCtx* const dctx = ZSTD_createDCtx();
        CHECK(dctx != NULL, "ZSTD_createDCtx() failed!");
        /* Set the maximum allowed window log.
         * The value 0 means use the default window log, which is equivalent to
         * not setting it.
         */
        CHECK_ZSTD( ZSTD_DCtx_setParameter(dctx, ZSTD_d_windowLogMax, wLog) );
        /* forces decompressor to use maximum memory size, since the
         * decompressed size is not stored in the frame header.
         */
        {   ZSTD_inBuffer inBuff = { compressedData, compressedSize, 0 };
            ZSTD_outBuffer outBuff = { decompressedData, sizeof(decompressedData), 0 };
            size_t const remaining = ZSTD_decompressStream(dctx, &outBuff, &inBuff);
            CHECK_ZSTD(remaining);
            CHECK(remaining == 0, "Frame not complete!");
            CHECK(outBuff.pos == sizeof(dataToCompress), "Bad decompression!");
        }

        size_t const cstreamSize = ZSTD_sizeof_CStream(cctx);
        size_t const cstreamEstimatedSize = ZSTD_estimateCStreamSize_usingCCtxParams(cctxParams);
        size_t const dstreamSize = ZSTD_sizeof_DStream(dctx);
        size_t const dstreamEstimatedSize = ZSTD_estimateDStreamSize_fromFrame(compressedData, compressedSize);

        CHECK(cstreamSize <= cstreamEstimatedSize, "Compression mem (%u) > estimated (%u)",
                (unsigned)cstreamSize, (unsigned)cstreamEstimatedSize);
        CHECK(dstreamSize <= dstreamEstimatedSize, "Decompression mem (%u) > estimated (%u)",
                (unsigned)dstreamSize, (unsigned)dstreamEstimatedSize);

        printf("Level %2i : Compression Mem = %5u KB (estimated : %5u KB) ; Decompression Mem = %4u KB (estimated : %5u KB)\n",
                compressionLevel,
                (unsigned)(cstreamSize>>10), (unsigned)(cstreamEstimatedSize>>10),
                (unsigned)(dstreamSize>>10), (unsigned)(dstreamEstimatedSize>>10));

        ZSTD_freeDCtx(dctx);
        ZSTD_freeCCtx(cctx);
        ZSTD_freeCCtxParams(cctxParams);
        if (wLog) break;  /* single test */
    }
    return 0;
}