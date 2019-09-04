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
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  scalar_t__ U64 ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,double const) ; 
 int FIO_compressFilename_srcFile (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char const*,char const*,int) ; 
 int /*<<< orphan*/  FIO_createCResources (int /*<<< orphan*/ * const,char const*,int,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIO_freeCResources (int /*<<< orphan*/  const) ; 
 scalar_t__ const UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ UTIL_getFileSize (char const*) ; 
 scalar_t__ const ZSTD_CONTENTSIZE_UNKNOWN ; 
 scalar_t__ const clock () ; 

int FIO_compressFilename(FIO_prefs_t* const prefs,
                         const char* dstFileName, const char* srcFileName,
                         const char* dictFileName, int compressionLevel,
                         ZSTD_compressionParameters comprParams)
{
    clock_t const start = clock();
    U64 const fileSize = UTIL_getFileSize(srcFileName);
    U64 const srcSize = (fileSize == UTIL_FILESIZE_UNKNOWN) ? ZSTD_CONTENTSIZE_UNKNOWN : fileSize;

    cRess_t const ress = FIO_createCResources(prefs, dictFileName, compressionLevel, srcSize, comprParams);
    int const result = FIO_compressFilename_srcFile(prefs, ress, dstFileName, srcFileName, compressionLevel);

    double const seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    DISPLAYLEVEL(4, "Completed in %.2f sec \n", seconds);

    FIO_freeCResources(ress);
    return result;
}