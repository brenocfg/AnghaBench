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
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  UTIL_time_t ;
typedef  int U64 ;
struct TYPE_4__ {int compressionType; int /*<<< orphan*/  checksumFlag; } ;
typedef  TYPE_1__ FIO_prefs_t ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,...) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*) ; 
 int FIO_compressGzFrame (int /*<<< orphan*/ *,char const*,int const,int,int*) ; 
 int FIO_compressLz4Frame (int /*<<< orphan*/ *,char const*,int const,int,int /*<<< orphan*/ ,int*) ; 
 int FIO_compressLzmaFrame (int /*<<< orphan*/ *,char const*,int const,int,int*,int) ; 
 int FIO_compressZstdFrame (TYPE_1__* const,int /*<<< orphan*/ *,char const*,int const,int,int*) ; 
#define  FIO_gzipCompression 132 
#define  FIO_lz4Compression 131 
#define  FIO_lzmaCompression 130 
#define  FIO_xzCompression 129 
#define  FIO_zstdCompression 128 
 int UTIL_clockSpanNano (int /*<<< orphan*/  const) ; 
 int UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 scalar_t__ clock () ; 

__attribute__((used)) static int
FIO_compressFilename_internal(FIO_prefs_t* const prefs,
                              cRess_t ress,
                              const char* dstFileName, const char* srcFileName,
                              int compressionLevel)
{
    UTIL_time_t const timeStart = UTIL_getTime();
    clock_t const cpuStart = clock();
    U64 readsize = 0;
    U64 compressedfilesize = 0;
    U64 const fileSize = UTIL_getFileSize(srcFileName);
    DISPLAYLEVEL(5, "%s: %u bytes \n", srcFileName, (unsigned)fileSize);

    /* compression format selection */
    switch (prefs->compressionType) {
        default:
        case FIO_zstdCompression:
            compressedfilesize = FIO_compressZstdFrame(prefs, &ress, srcFileName, fileSize, compressionLevel, &readsize);
            break;

        case FIO_gzipCompression:
#ifdef ZSTD_GZCOMPRESS
            compressedfilesize = FIO_compressGzFrame(&ress, srcFileName, fileSize, compressionLevel, &readsize);
#else
            (void)compressionLevel;
            EXM_THROW(20, "zstd: %s: file cannot be compressed as gzip (zstd compiled without ZSTD_GZCOMPRESS) -- ignored \n",
                            srcFileName);
#endif
            break;

        case FIO_xzCompression:
        case FIO_lzmaCompression:
#ifdef ZSTD_LZMACOMPRESS
            compressedfilesize = FIO_compressLzmaFrame(&ress, srcFileName, fileSize, compressionLevel, &readsize, prefs->compressionType==FIO_lzmaCompression);
#else
            (void)compressionLevel;
            EXM_THROW(20, "zstd: %s: file cannot be compressed as xz/lzma (zstd compiled without ZSTD_LZMACOMPRESS) -- ignored \n",
                            srcFileName);
#endif
            break;

        case FIO_lz4Compression:
#ifdef ZSTD_LZ4COMPRESS
            compressedfilesize = FIO_compressLz4Frame(&ress, srcFileName, fileSize, compressionLevel, prefs->checksumFlag, &readsize);
#else
            (void)compressionLevel;
            EXM_THROW(20, "zstd: %s: file cannot be compressed as lz4 (zstd compiled without ZSTD_LZ4COMPRESS) -- ignored \n",
                            srcFileName);
#endif
            break;
    }

    /* Status */
    DISPLAYLEVEL(2, "\r%79s\r", "");
    DISPLAYLEVEL(2,"%-20s :%6.2f%%   (%6llu => %6llu bytes, %s) \n",
        srcFileName,
        (double)compressedfilesize / (readsize+(!readsize)/*avoid div by zero*/) * 100,
        (unsigned long long)readsize, (unsigned long long) compressedfilesize,
         dstFileName);

    /* Elapsed Time and CPU Load */
    {   clock_t const cpuEnd = clock();
        double const cpuLoad_s = (double)(cpuEnd - cpuStart) / CLOCKS_PER_SEC;
        U64 const timeLength_ns = UTIL_clockSpanNano(timeStart);
        double const timeLength_s = (double)timeLength_ns / 1000000000;
        double const cpuLoad_pct = (cpuLoad_s / timeLength_s) * 100;
        DISPLAYLEVEL(4, "%-20s : Completed in %.2f sec  (cpu load : %.0f%%)\n",
                        srcFileName, timeLength_s, cpuLoad_pct);
    }
    return 0;
}