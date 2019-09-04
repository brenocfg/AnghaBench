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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ * const) ; 
 scalar_t__ isDirectory (char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void loadFile(void* buffer, const char* fileName, size_t fileSize)
{
    FILE* const f = fopen(fileName, "rb");
    if (isDirectory(fileName)) {
        fprintf(stderr, "Ignoring %s directory \n", fileName);
        exit(2);
    }
    if (f==NULL) {
        fprintf(stderr, "Impossible to open %s \n", fileName);
        exit(3);
    }
    {   size_t const readSize = fread(buffer, 1, fileSize, f);
        if (readSize != fileSize) {
            fprintf(stderr, "Error reading %s \n", fileName);
            exit(5);
    }   }
    fclose(f);
}