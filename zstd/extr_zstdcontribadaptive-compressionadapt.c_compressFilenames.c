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
 int compressFilename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdoutmark ; 

__attribute__((used)) static int compressFilenames(const char** filenameTable, unsigned numFiles, unsigned forceStdout)
{
    int ret = 0;
    unsigned fileNum;
    for (fileNum=0; fileNum<numFiles; fileNum++) {
        const char* filename = filenameTable[fileNum];
        if (!forceStdout) {
            ret |= compressFilename(filename, NULL);
        }
        else {
            ret |= compressFilename(filename, stdoutmark);
        }

    }
    return ret;
}