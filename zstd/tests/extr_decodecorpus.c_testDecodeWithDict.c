#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ genType_e ;
struct TYPE_4__ {scalar_t__ srcStart; scalar_t__ src; scalar_t__ dataStart; scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
typedef  int /*<<< orphan*/  dictInfo ;
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DECOMPRESSED_BUFFER ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t MAX (size_t const,int) ; 
 int /*<<< orphan*/  MAX_DECOMPRESSED_SIZE ; 
 int RAND (int*) ; 
 int ZDICT_CONTENTSIZE_MIN ; 
 int ZDICT_DICTSIZE_MIN ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 size_t ZSTD_decompressBegin_usingDict (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,size_t const) ; 
 size_t ZSTD_decompressBlock (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 size_t ZSTD_decompress_usingDict (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ * const,size_t const) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ * const) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ * const) ; 
 scalar_t__ genRandomDict (int const,int,size_t const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  generateCompressedBlock (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generateFrame (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gt_frame ; 
 int /*<<< orphan*/  initDictInfo (int,size_t const,int /*<<< orphan*/ * const,int const) ; 
 int /*<<< orphan*/ * malloc (size_t const) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static size_t testDecodeWithDict(U32 seed, genType_e genType)
{
    /* create variables */
    size_t const dictSize = RAND(&seed) % (10 << 20) + ZDICT_DICTSIZE_MIN + ZDICT_CONTENTSIZE_MIN;
    U32 const dictID = RAND(&seed);
    size_t errorDetected = 0;
    BYTE* const fullDict = malloc(dictSize);
    if (fullDict == NULL) {
        return ERROR(GENERIC);
    }

    /* generate random dictionary */
    if (genRandomDict(dictID, seed, dictSize, fullDict)) {  /* return 0 on success */
        errorDetected = ERROR(GENERIC);
        goto dictTestCleanup;
    }


    {   frame_t fr;
        dictInfo info;
        ZSTD_DCtx* const dctx = ZSTD_createDCtx();
        size_t ret;

        /* get dict info */
        {   size_t const headerSize = MAX(dictSize/4, 256);
            size_t const dictContentSize = dictSize-headerSize;
            BYTE* const dictContent = fullDict+headerSize;
            info = initDictInfo(1, dictContentSize, dictContent, dictID);
        }

        /* manually decompress and check difference */
        if (genType == gt_frame) {
            /* Test frame */
            generateFrame(seed, &fr, info);
            ret = ZSTD_decompress_usingDict(dctx, DECOMPRESSED_BUFFER, MAX_DECOMPRESSED_SIZE,
                                            fr.dataStart, (BYTE*)fr.data - (BYTE*)fr.dataStart,
                                            fullDict, dictSize);
        } else {
            /* Test block */
            generateCompressedBlock(seed, &fr, info);
            ret = ZSTD_decompressBegin_usingDict(dctx, fullDict, dictSize);
            if (ZSTD_isError(ret)) {
                errorDetected = ret;
                ZSTD_freeDCtx(dctx);
                goto dictTestCleanup;
            }
            ret = ZSTD_decompressBlock(dctx, DECOMPRESSED_BUFFER, MAX_DECOMPRESSED_SIZE,
                                       fr.dataStart, (BYTE*)fr.data - (BYTE*)fr.dataStart);
        }
        ZSTD_freeDCtx(dctx);

        if (ZSTD_isError(ret)) {
            errorDetected = ret;
            goto dictTestCleanup;
        }

        if (memcmp(DECOMPRESSED_BUFFER, fr.srcStart, (BYTE*)fr.src - (BYTE*)fr.srcStart) != 0) {
            errorDetected = ERROR(corruption_detected);
            goto dictTestCleanup;
        }
    }

dictTestCleanup:
    free(fullDict);
    return errorDetected;
}