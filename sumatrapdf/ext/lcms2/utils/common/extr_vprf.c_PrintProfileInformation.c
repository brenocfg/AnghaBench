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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  PrintColorantTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PrintInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Verbose ; 
 int /*<<< orphan*/  cmsInfoCopyright ; 
 int /*<<< orphan*/  cmsInfoDescription ; 
 int /*<<< orphan*/  cmsInfoManufacturer ; 
 int /*<<< orphan*/  cmsInfoModel ; 
 int /*<<< orphan*/  cmsSigColorantTableOutTag ; 
 int /*<<< orphan*/  cmsSigColorantTableTag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

void PrintProfileInformation(cmsContext ContextID, cmsHPROFILE hInput)
{
    if (hInput == NULL) {
			fprintf(stderr, "*Wrong or corrupted profile*\n");
            return;
    }

    PrintInfo(ContextID, hInput, cmsInfoDescription);
    PrintInfo(ContextID, hInput, cmsInfoManufacturer);
    PrintInfo(ContextID, hInput, cmsInfoModel);
    PrintInfo(ContextID, hInput, cmsInfoCopyright);

    if (Verbose > 2) {

        PrintColorantTable(ContextID, hInput, cmsSigColorantTableTag,    "Input colorant table");
        PrintColorantTable(ContextID, hInput, cmsSigColorantTableOutTag, "Input colorant out table");
    }

    printf("\n");
}