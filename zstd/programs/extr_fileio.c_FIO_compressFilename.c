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
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;

/* Variables and functions */
 int FIO_compressFilename_srcFile (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char const*,char const*,int) ; 
 int /*<<< orphan*/  FIO_createCResources (int /*<<< orphan*/ * const,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIO_freeCResources (int /*<<< orphan*/  const) ; 

int FIO_compressFilename(FIO_prefs_t* const prefs, const char* dstFileName,
                         const char* srcFileName, const char* dictFileName,
                         int compressionLevel,  ZSTD_compressionParameters comprParams)
{
    cRess_t const ress = FIO_createCResources(prefs, dictFileName, compressionLevel, comprParams);
    int const result = FIO_compressFilename_srcFile(prefs, ress, dstFileName, srcFileName, compressionLevel);


    FIO_freeCResources(ress);
    return result;
}