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
 scalar_t__ ARCH_ARM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ giArch ; 

void
Output_stublabel(FILE *fileDest, char* pszSymbolName)
{
    if (giArch == ARCH_ARM)
    {
        fprintf(fileDest,
                "\tEXPORT |%s| [FUNC]\n|%s|\n",
                pszSymbolName,
                pszSymbolName);
    }
    else
    {
        fprintf(fileDest,
                "PUBLIC %s\n%s: nop\n",
                pszSymbolName,
                pszSymbolName);
    }
}