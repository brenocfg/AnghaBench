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
 int /*<<< orphan*/  BMK_benchFileTable (char const**,unsigned int,char const*,int,int) ; 
 int /*<<< orphan*/  BMK_syntheticTest (int,int,double const) ; 
 scalar_t__ g_compressibilityDefault ; 

int BMK_benchFiles(const char** fileNamesTable, unsigned nbFiles,
                   const char* dictFileName, int cLevel, int cLevelLast)
{
    double const compressibility = (double)g_compressibilityDefault / 100;

    if (nbFiles == 0)
        BMK_syntheticTest(cLevel, cLevelLast, compressibility);
    else
        BMK_benchFileTable(fileNamesTable, nbFiles, dictFileName, cLevel, cLevelLast);
    return 0;
}