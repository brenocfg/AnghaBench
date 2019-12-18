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

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 unsigned int XXH32 (void const*,size_t const,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compress (void*,size_t,void const*,size_t,int const) ; 
 size_t ZSTD_decompress (void*,size_t,void*,size_t const) ; 
 char* ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t roundTripTest(void* resultBuff, size_t resultBuffCapacity,
                            void* compressedBuff, size_t compressedBuffCapacity,
                      const void* srcBuff, size_t srcBuffSize)
{
    static const int maxClevel = 19;
    size_t const hashLength = MIN(128, srcBuffSize);
    unsigned const h32 = XXH32(srcBuff, hashLength, 0);
    int const cLevel = h32 % maxClevel;
    size_t const cSize = ZSTD_compress(compressedBuff, compressedBuffCapacity, srcBuff, srcBuffSize, cLevel);
    if (ZSTD_isError(cSize)) {
        fprintf(stderr, "Compression error : %s \n", ZSTD_getErrorName(cSize));
        return cSize;
    }
    return ZSTD_decompress(resultBuff, resultBuffCapacity, compressedBuff, cSize);
}