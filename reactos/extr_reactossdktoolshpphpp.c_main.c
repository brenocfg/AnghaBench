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
 int ParseInputFile (char*,int /*<<< orphan*/ *) ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

int
main(int argc, char* argv[])
{
    char *pszInFile, *pszOutFile;
    FILE* fileOut;
    int ret;

    if (argc != 3)
    {
        error("Usage: hpp <inputfile> <outputfile>\n");
        exit(1);
    }

    pszInFile = convert_path(argv[1]);
    pszOutFile = convert_path(argv[2]);

    fileOut = fopen(pszOutFile, "wb");
    if (fileOut == NULL)
    {
        error("Cannot open output file %s", pszOutFile);
        exit(1);
    }

    ret = ParseInputFile(pszInFile, fileOut);

    fclose(fileOut);
    free(pszInFile);
    free(pszOutFile);

    return ret;
}