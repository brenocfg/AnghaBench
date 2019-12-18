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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

void*
LoadFile(const char* pszFileName, size_t* pFileSize)
{
    FILE* file;
    void* pFileData = NULL;
    int iFileSize;

    trace("Loading file...");

    file = fopen(pszFileName, "rb");
    if (!file)
    {
        trace("Could not open file\n");
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    iFileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    *pFileSize = iFileSize;
    trace("ok. Size is %d\n", iFileSize);

    pFileData = malloc(iFileSize + 1);

    if (pFileData != NULL)
    {
        if (iFileSize != fread(pFileData, 1, iFileSize, file))
        {
            free(pFileData);
            pFileData = NULL;
        }
    }
    else
    {
        trace("Could not allocate memory for file\n");
    }

    fclose(file);

    return pFileData;
}