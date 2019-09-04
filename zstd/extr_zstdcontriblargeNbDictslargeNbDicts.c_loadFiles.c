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
typedef  scalar_t__ U64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ UTIL_getFileSize (char const* const) ; 
 scalar_t__ UTIL_isDirectory (char const* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int loadFiles(void* buffer, size_t bufferSize,
                     size_t* fileSizes,
                     const char* const * fileNamesTable, unsigned nbFiles)
{
    size_t pos = 0, totalSize = 0;

    for (unsigned n=0; n<nbFiles; n++) {
        U64 fileSize = UTIL_getFileSize(fileNamesTable[n]);
        if (UTIL_isDirectory(fileNamesTable[n])) {
            fileSizes[n] = 0;
            continue;
        }
        if (fileSize == UTIL_FILESIZE_UNKNOWN) {
            fileSizes[n] = 0;
            continue;
        }

        FILE* const f = fopen(fileNamesTable[n], "rb");
        assert(f!=NULL);

        assert(pos <= bufferSize);
        assert(fileSize <= bufferSize - pos);

        {   size_t const readSize = fread(((char*)buffer)+pos, 1, (size_t)fileSize, f);
            assert(readSize == fileSize);
            pos += readSize;
        }
        fileSizes[n] = (size_t)fileSize;
        totalSize += (size_t)fileSize;
        fclose(f);
    }

    assert(totalSize == bufferSize);
    return 0;
}