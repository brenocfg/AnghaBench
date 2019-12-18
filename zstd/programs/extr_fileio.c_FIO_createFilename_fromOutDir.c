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
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 char* extractFilename (char const*,char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char*
FIO_createFilename_fromOutDir(const char* path, const char* outDirName, const size_t suffixLen)
{
    const char* filenameStart;
    char separator;
    char* result;

#if defined(_MSC_VER) || defined(__MINGW32__) || defined (__MSVCRT__) /* windows support */
    separator = '\\';
#else
    separator = '/';
#endif

    filenameStart = extractFilename(path, separator);
#if defined(_MSC_VER) || defined(__MINGW32__) || defined (__MSVCRT__) /* windows support */
    filenameStart = extractFilename(filenameStart, '/');  /* sometimes, '/' separator is also used on Windows (mingw+msys2) */
#endif

    result = (char*) calloc(1, strlen(outDirName) + 1 + strlen(filenameStart) + suffixLen + 1);
    if (!result) {
        EXM_THROW(30, "zstd: FIO_createFilename_fromOutDir: %s", strerror(errno));
    }

    memcpy(result, outDirName, strlen(outDirName));
    if (outDirName[strlen(outDirName)-1] == separator) {
        memcpy(result + strlen(outDirName), filenameStart, strlen(filenameStart));
    } else {
        memcpy(result + strlen(outDirName), &separator, 1);
        memcpy(result + strlen(outDirName) + 1, filenameStart, strlen(filenameStart));
    }

    return result;
}