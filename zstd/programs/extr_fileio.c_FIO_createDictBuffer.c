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
typedef  int U64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DICTSIZE_MAX ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,char const*) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 int UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 void* malloc (size_t) ; 
 int strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t FIO_createDictBuffer(void** bufferPtr, const char* fileName)
{
    FILE* fileHandle;
    U64 fileSize;

    assert(bufferPtr != NULL);
    *bufferPtr = NULL;
    if (fileName == NULL) return 0;

    DISPLAYLEVEL(4,"Loading %s as dictionary \n", fileName);
    fileHandle = fopen(fileName, "rb");
    if (fileHandle==NULL) EXM_THROW(31, "%s: %s", fileName, strerror(errno));

    fileSize = UTIL_getFileSize(fileName);
    if (fileSize > DICTSIZE_MAX) {
        EXM_THROW(32, "Dictionary file %s is too large (> %u MB)",
                        fileName, DICTSIZE_MAX >> 20);   /* avoid extreme cases */
    }
    *bufferPtr = malloc((size_t)fileSize);
    if (*bufferPtr==NULL) EXM_THROW(34, "%s", strerror(errno));
    {   size_t const readSize = fread(*bufferPtr, 1, (size_t)fileSize, fileHandle);
        if (readSize != fileSize)
            EXM_THROW(35, "Error reading dictionary file %s : %s",
                    fileName, strerror(errno));
    }
    fclose(fileHandle);
    return (size_t)fileSize;
}