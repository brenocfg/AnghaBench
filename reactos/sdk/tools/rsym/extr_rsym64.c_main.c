#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  FilePtr; TYPE_1__* OptionalHeader; int /*<<< orphan*/  AlignBuf; int /*<<< orphan*/  cbInFileSize; } ;
struct TYPE_6__ {int /*<<< orphan*/  FileAlignment; } ;
typedef  TYPE_2__ FILE_INFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GeneratePData (TYPE_2__*) ; 
 int ParsePEHeaders (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteOutFile (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* argv[])
{
    char* pszInFile;
    char* pszOutFile;
    FILE_INFO File;
    FILE* outfile;
    int ret;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: rsym <exefile> <symfile>\n");
        exit(1);
    }

    pszInFile = convert_path(argv[1]);
    pszOutFile = convert_path(argv[2]);

    File.FilePtr = load_file(pszInFile, &File.cbInFileSize);
    if (!File.FilePtr)
    {
        fprintf(stderr, "An error occured loading '%s'\n", pszInFile);
        exit(1);
    }

    ret = ParsePEHeaders(&File);
    if (ret != 1)
    {
        free(File.FilePtr);
        exit(ret == -1 ? 1 : 0);
    }

    File.AlignBuf = malloc(File.OptionalHeader->FileAlignment);
    memset(File.AlignBuf, 0, File.OptionalHeader->FileAlignment);

    GeneratePData(&File);

    outfile = fopen(pszOutFile, "wb");
    if (outfile == NULL)
    {
        perror("Cannot open output file");
        free(File.FilePtr);
        exit(1);
    }

    WriteOutFile(outfile, &File);

    fclose(outfile);

    return 0;
}