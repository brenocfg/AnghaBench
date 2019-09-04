#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ srcBufferLoaded; } ;
typedef  TYPE_1__ dRess_t ;
struct TYPE_8__ {scalar_t__ removeSrcFile; } ;
typedef  TYPE_2__ FIO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,...) ; 
 int FIO_decompressDstFile (TYPE_2__* const,TYPE_1__,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * FIO_openSrcFile (char const*) ; 
 scalar_t__ FIO_remove (char const*) ; 
 scalar_t__ UTIL_isDirectory (char const*) ; 
 int /*<<< orphan*/  clearHandler () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdinmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FIO_decompressSrcFile(FIO_prefs_t* const prefs, dRess_t ress, const char* dstFileName, const char* srcFileName)
{
    FILE* srcFile;
    int result;

    if (UTIL_isDirectory(srcFileName)) {
        DISPLAYLEVEL(1, "zstd: %s is a directory -- ignored \n", srcFileName);
        return 1;
    }

    srcFile = FIO_openSrcFile(srcFileName);
    if (srcFile==NULL) return 1;
    ress.srcBufferLoaded = 0;

    result = FIO_decompressDstFile(prefs, ress, srcFile, dstFileName, srcFileName);

    /* Close file */
    if (fclose(srcFile)) {
        DISPLAYLEVEL(1, "zstd: %s: %s \n", srcFileName, strerror(errno));  /* error should not happen */
        return 1;
    }
    if ( prefs->removeSrcFile  /* --rm */
      && (result==0)      /* decompression successful */
      && strcmp(srcFileName, stdinmark) ) /* not stdin */ {
        /* We must clear the handler, since after this point calling it would
         * delete both the source and destination files.
         */
        clearHandler();
        if (FIO_remove(srcFileName)) {
            /* failed to remove src file */
            DISPLAYLEVEL(1, "zstd: %s: %s \n", srcFileName, strerror(errno));
            return 1;
    }   }
    return result;
}