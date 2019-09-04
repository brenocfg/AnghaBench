#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dstFile; } ;
typedef  TYPE_1__ dRess_t ;
typedef  int /*<<< orphan*/  FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*) ; 
 TYPE_1__ FIO_createDResources (int /*<<< orphan*/ * const,char const*) ; 
 int FIO_decompressSrcFile (int /*<<< orphan*/ * const,TYPE_1__,char const* const,char const* const) ; 
 char* FIO_determineDstName (char const* const) ; 
 int /*<<< orphan*/  FIO_freeDResources (TYPE_1__) ; 
 scalar_t__ FIO_openDstFile (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (scalar_t__) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

int
FIO_decompressMultipleFilenames(FIO_prefs_t* const prefs,
                                const char* srcNamesTable[], unsigned nbFiles,
                                const char* outFileName,
                                const char* dictFileName)
{
    int error = 0;
    dRess_t ress = FIO_createDResources(prefs, dictFileName);

    if (outFileName) {
        unsigned u;
        ress.dstFile = FIO_openDstFile(prefs, NULL, outFileName);
        if (ress.dstFile == 0) EXM_THROW(71, "cannot open %s", outFileName);
        for (u=0; u<nbFiles; u++)
            error |= FIO_decompressSrcFile(prefs, ress, outFileName, srcNamesTable[u]);
        if (fclose(ress.dstFile))
            EXM_THROW(72, "Write error : %s : cannot properly close output file",
                        strerror(errno));
    } else {
        unsigned u;
        for (u=0; u<nbFiles; u++) {   /* create dstFileName */
            const char* const srcFileName = srcNamesTable[u];
            const char* const dstFileName = FIO_determineDstName(srcFileName);
            if (dstFileName == NULL) { error=1; continue; }

            error |= FIO_decompressSrcFile(prefs, ress, dstFileName, srcFileName);
        }
    }

    FIO_freeDResources(ress);
    return error;
}