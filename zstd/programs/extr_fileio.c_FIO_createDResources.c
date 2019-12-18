#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ress ;
struct TYPE_6__ {int /*<<< orphan*/ * dctx; void* dstBuffer; void* srcBuffer; int /*<<< orphan*/  dstBufferSize; int /*<<< orphan*/  srcBufferSize; } ;
typedef  TYPE_1__ dRess_t ;
struct TYPE_7__ {int /*<<< orphan*/  memLimit; } ;
typedef  TYPE_2__ FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 size_t FIO_createDictBuffer (void**,char const*) ; 
 int /*<<< orphan*/  ZSTD_DCtx_setMaxWindowSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_DStreamInSize () ; 
 int /*<<< orphan*/  ZSTD_DStreamOutSize () ; 
 int /*<<< orphan*/ * ZSTD_createDStream () ; 
 int /*<<< orphan*/  ZSTD_initDStream_usingDict (int /*<<< orphan*/ *,void*,size_t const) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dRess_t FIO_createDResources(FIO_prefs_t* const prefs, const char* dictFileName)
{
    dRess_t ress;
    memset(&ress, 0, sizeof(ress));

    /* Allocation */
    ress.dctx = ZSTD_createDStream();
    if (ress.dctx==NULL)
        EXM_THROW(60, "Error: %s : can't create ZSTD_DStream", strerror(errno));
    CHECK( ZSTD_DCtx_setMaxWindowSize(ress.dctx, prefs->memLimit) );
    ress.srcBufferSize = ZSTD_DStreamInSize();
    ress.srcBuffer = malloc(ress.srcBufferSize);
    ress.dstBufferSize = ZSTD_DStreamOutSize();
    ress.dstBuffer = malloc(ress.dstBufferSize);
    if (!ress.srcBuffer || !ress.dstBuffer)
        EXM_THROW(61, "Allocation error : not enough memory");

    /* dictionary */
    {   void* dictBuffer;
        size_t const dictBufferSize = FIO_createDictBuffer(&dictBuffer, dictFileName);
        CHECK( ZSTD_initDStream_usingDict(ress.dctx, dictBuffer, dictBufferSize) );
        free(dictBuffer);
    }

    return ress;
}