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
 int /*<<< orphan*/  CHECK (int,char*) ; 
 int /*<<< orphan*/  ERROR_fread ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen_orDie (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 size_t fread (void*,int,size_t const,int /*<<< orphan*/ * const) ; 
 size_t fsize_orDie (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t loadFile_orDie(const char* fileName, void* buffer, size_t bufferSize)
{
    size_t const fileSize = fsize_orDie(fileName);
    CHECK(fileSize <= bufferSize, "File too large!");

    FILE* const inFile = fopen_orDie(fileName, "rb");
    size_t const readSize = fread(buffer, 1, fileSize, inFile);
    if (readSize != (size_t)fileSize) {
        fprintf(stderr, "fread: %s : %s \n", fileName, strerror(errno));
        exit(ERROR_fread);
    }
    fclose(inFile);  /* can't fail, read only */
    return fileSize;
}