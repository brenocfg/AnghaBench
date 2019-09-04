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
typedef  int /*<<< orphan*/ * PROPINFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBitBlt (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  CreatePrimitive (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateShiftTables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateTable (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * FindRopInfo (unsigned int) ; 
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*) ; 
 unsigned int ROPCODE_GENERIC ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
Generate(char *OutputDir, unsigned Bpp)
{
    FILE *Out;
    unsigned RopCode;
    PROPINFO RopInfo;
    char *FileName;

    FileName = malloc(strlen(OutputDir) + 12);
    if (NULL == FileName)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    strcpy(FileName, OutputDir);
    if ('/' != FileName[strlen(FileName) - 1])
    {
        strcat(FileName, "/");
    }
    sprintf(FileName + strlen(FileName), "dib%ugen.c", Bpp);

    Out = fopen(FileName, "w");
    free(FileName);
    if (NULL == Out)
    {
        perror("Error opening output file");
        exit(1);
    }

    MARK(Out);
    Output(Out, "/* This is a generated file. Please do not edit */\n");
    Output(Out, "\n");
    Output(Out, "#include <win32k.h>\n");
    CreateShiftTables(Out);

    RopInfo = FindRopInfo(ROPCODE_GENERIC);
    CreatePrimitive(Out, Bpp, RopInfo);
    for (RopCode = 0; RopCode < 256; RopCode++)
    {
        RopInfo = FindRopInfo(RopCode);
        if (NULL != RopInfo)
        {
            CreatePrimitive(Out, Bpp, RopInfo);
        }
    }
    CreateTable(Out, Bpp);
    CreateBitBlt(Out, Bpp);

    fclose(Out);
}