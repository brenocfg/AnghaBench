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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UTIL_fileExist (char const*) ; 
 int /*<<< orphan*/  UTIL_isFIFO (char const*) ; 
 int /*<<< orphan*/  UTIL_isRegularFile (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE* FIO_openSrcFile(const char* srcFileName)
{
    assert(srcFileName != NULL);
    if (!strcmp (srcFileName, stdinmark)) {
        DISPLAYLEVEL(4,"Using stdin for input \n");
        SET_BINARY_MODE(stdin);
        return stdin;
    }

    if (!UTIL_fileExist(srcFileName)) {
        DISPLAYLEVEL(1, "zstd: can't stat %s : %s -- ignored \n",
                        srcFileName, strerror(errno));
        return NULL;
    }

    if (!UTIL_isRegularFile(srcFileName)
#ifndef _MSC_VER
        && !UTIL_isFIFO(srcFileName)
#endif /* _MSC_VER */
    ) {
        DISPLAYLEVEL(1, "zstd: %s is not a regular file -- ignored \n",
                        srcFileName);
        return NULL;
    }

    {   FILE* const f = fopen(srcFileName, "rb");
        if (f == NULL)
            DISPLAYLEVEL(1, "zstd: %s: %s \n", srcFileName, strerror(errno));
        return f;
    }
}