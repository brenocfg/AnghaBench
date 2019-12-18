#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stat_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dstFile; } ;
typedef  TYPE_1__ dRess_t ;
struct TYPE_9__ {scalar_t__ testMode; } ;
typedef  TYPE_2__ FIO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int FIO_decompressFrames (TYPE_2__* const,TYPE_1__,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * FIO_openDstFile (TYPE_2__* const,char const*,char const*) ; 
 int /*<<< orphan*/  FIO_remove (char const*) ; 
 scalar_t__ UTIL_getFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTIL_setFileStat (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addHandler (char const*) ; 
 int /*<<< orphan*/  clearHandler () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  nulmark ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  stdoutmark ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FIO_decompressDstFile(FIO_prefs_t* const prefs,
                                 dRess_t ress, FILE* srcFile,
                                 const char* dstFileName, const char* srcFileName)
{
    int result;
    stat_t statbuf;
    int transfer_permissions = 0;
    int releaseDstFile = 0;

    if ((ress.dstFile == NULL) && (prefs->testMode==0)) {
        releaseDstFile = 1;

        ress.dstFile = FIO_openDstFile(prefs, srcFileName, dstFileName);
        if (ress.dstFile==NULL) return 1;

        /* Must only be added after FIO_openDstFile() succeeds.
         * Otherwise we may delete the destination file if it already exists,
         * and the user presses Ctrl-C when asked if they wish to overwrite.
         */
        addHandler(dstFileName);

        if ( strcmp(srcFileName, stdinmark)   /* special case : don't transfer permissions from stdin */
          && UTIL_getFileStat(srcFileName, &statbuf) )
            transfer_permissions = 1;
    }

    result = FIO_decompressFrames(prefs, ress, srcFile, dstFileName, srcFileName);

    if (releaseDstFile) {
        FILE* const dstFile = ress.dstFile;
        clearHandler();
        ress.dstFile = NULL;
        if (fclose(dstFile)) {
            DISPLAYLEVEL(1, "zstd: %s: %s \n", dstFileName, strerror(errno));
            result = 1;
        }

        if ( (result != 0)  /* operation failure */
          && strcmp(dstFileName, nulmark)     /* special case : don't remove() /dev/null (#316) */
          && strcmp(dstFileName, stdoutmark)  /* special case : don't remove() stdout */
          ) {
            FIO_remove(dstFileName);  /* remove decompression artefact; note: don't do anything special if remove() fails */
        } else {  /* operation success */
            if ( strcmp(dstFileName, stdoutmark) /* special case : don't chmod stdout */
              && strcmp(dstFileName, nulmark)    /* special case : don't chmod /dev/null */
              && transfer_permissions )          /* file permissions correctly extracted from src */
                UTIL_setFileStat(dstFileName, &statbuf);  /* transfer file permissions from src into dst */
        }
    }

    return result;
}