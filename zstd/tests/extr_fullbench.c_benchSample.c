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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  RDG_genBuffer (void* const,size_t,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  benchMem (int,void* const,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static int benchSample(U32 benchNb,
                       size_t benchedSize, double compressibility,
                       int cLevel, ZSTD_compressionParameters cparams)
{
    /* Allocation */
    void* const origBuff = malloc(benchedSize);
    if (!origBuff) { DISPLAY("\nError: not enough memory!\n"); return 12; }

    /* Fill buffer */
    RDG_genBuffer(origBuff, benchedSize, compressibility, 0.0, 0);

    /* bench */
    DISPLAY("\r%70s\r", "");
    DISPLAY(" Sample %u bytes : \n", (unsigned)benchedSize);
    if (benchNb) {
        benchMem(benchNb, origBuff, benchedSize, cLevel, cparams);
    } else {  /* 0 == run all tests */
        for (benchNb=0; benchNb<100; benchNb++) {
            benchMem(benchNb, origBuff, benchedSize, cLevel, cparams);
    }   }

    free(origBuff);
    return 0;
}