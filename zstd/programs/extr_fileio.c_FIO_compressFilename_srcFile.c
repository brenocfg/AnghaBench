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
struct TYPE_7__ {int /*<<< orphan*/ * srcFile; int /*<<< orphan*/ * dictFileName; } ;
typedef  TYPE_1__ cRess_t ;
struct TYPE_8__ {int excludeCompressedFiles; scalar_t__ removeSrcFile; } ;
typedef  TYPE_2__ FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int FIO_compressFilename_dstFile (TYPE_2__* const,TYPE_1__,char const*,char const*,int) ; 
 int /*<<< orphan*/ * FIO_openSrcFile (char const*) ; 
 scalar_t__ FIO_remove (char const*) ; 
 scalar_t__ UTIL_isCompressedFile (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ UTIL_isDirectory (char const*) ; 
 scalar_t__ UTIL_isSameFile (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearHandler () ; 
 int /*<<< orphan*/  compressedFileExtensions ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdinmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FIO_compressFilename_srcFile(FIO_prefs_t* const prefs,
                             cRess_t ress,
                             const char* dstFileName,
                             const char* srcFileName,
                             int compressionLevel)
{
    int result;

    /* ensure src is not a directory */
    if (UTIL_isDirectory(srcFileName)) {
        DISPLAYLEVEL(1, "zstd: %s is a directory -- ignored \n", srcFileName);
        return 1;
    }

    /* ensure src is not the same as dict (if present) */
    if (ress.dictFileName != NULL && UTIL_isSameFile(srcFileName, ress.dictFileName)) {
        DISPLAYLEVEL(1, "zstd: cannot use %s as an input file and dictionary \n", srcFileName);
        return 1;
    }

    /* Check if "srcFile" is compressed. Only done if --exclude-compressed flag is used
    * YES => ZSTD will skip compression of the file and will return 0.
    * NO => ZSTD will resume with compress operation.
    */
    if (prefs->excludeCompressedFiles == 1 && UTIL_isCompressedFile(srcFileName, compressedFileExtensions)) {
        DISPLAYLEVEL(4, "File is already compressed : %s \n", srcFileName);
        return 0;
    }

    ress.srcFile = FIO_openSrcFile(srcFileName);
    if (ress.srcFile == NULL) return 1;   /* srcFile could not be opened */

    result = FIO_compressFilename_dstFile(prefs, ress, dstFileName, srcFileName, compressionLevel);

    fclose(ress.srcFile);
    ress.srcFile = NULL;
    if ( prefs->removeSrcFile   /* --rm */
      && result == 0       /* success */
      && strcmp(srcFileName, stdinmark)   /* exception : don't erase stdin */
      ) {
        /* We must clear the handler, since after this point calling it would
         * delete both the source and destination files.
         */
        clearHandler();
        if (FIO_remove(srcFileName))
            EXM_THROW(1, "zstd: %s: %s", srcFileName, strerror(errno));
    }
    return result;
}