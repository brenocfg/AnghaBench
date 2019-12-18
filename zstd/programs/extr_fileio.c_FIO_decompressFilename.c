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
typedef  int /*<<< orphan*/  dRess_t ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIO_createDResources (int /*<<< orphan*/ * const,char const*) ; 
 int FIO_decompressSrcFile (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,char const*,char const*) ; 
 int /*<<< orphan*/  FIO_freeDResources (int /*<<< orphan*/  const) ; 

int FIO_decompressFilename(FIO_prefs_t* const prefs,
                           const char* dstFileName, const char* srcFileName,
                           const char* dictFileName)
{
    dRess_t const ress = FIO_createDResources(prefs, dictFileName);

    int const decodingError = FIO_decompressSrcFile(prefs, ress, dstFileName, srcFileName);

    FIO_freeDResources(ress);
    return decodingError;
}