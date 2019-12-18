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
 scalar_t__ ARCH_AMD64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ giArch ; 

void
OutputHeader_asmstub(FILE *file, char *libname)
{
    fprintf(file, "; File generated automatically, do not edit! \n\n");

    if (giArch == ARCH_X86)
    {
        fprintf(file, ".586\n.model flat\n.code\n");
    }
    else if (giArch == ARCH_AMD64)
    {
        fprintf(file, ".code\n");
    }
    else if (giArch == ARCH_ARM)
    {
        fprintf(file, "    AREA |.text|,ALIGN=2,CODE,READONLY\n\n");
    }
}