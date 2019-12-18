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
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  CGATSoutFilename ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int /*<<< orphan*/  SetOutputDataFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8Alloc (int /*<<< orphan*/ *) ; 
 scalar_t__ cmsIT8GetPropertyDbl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * cmsIT8LoadFromFile (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cmsMAX_PATH ; 
 int /*<<< orphan*/ * hIT8in ; 
 int /*<<< orphan*/  hIT8out ; 
 int nMaxPatches ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int xoptind ; 

__attribute__((used)) static
void OpenCGATSFiles(cmsContext ContextID, int argc, char *argv[])
{
    int nParams = argc - xoptind;

    if (nParams >= 1)  {

        hIT8in = cmsIT8LoadFromFile(0, argv[xoptind]);

        if (hIT8in == NULL)
            FatalError("'%s' is not recognized as a CGATS file", argv[xoptind]);

        nMaxPatches = (int) cmsIT8GetPropertyDbl(ContextID, hIT8in, "NUMBER_OF_SETS");
    }

    if (nParams == 2) {

        hIT8out = cmsIT8Alloc(NULL);
        SetOutputDataFormat(ContextID);
        strncpy(CGATSoutFilename, argv[xoptind+1], cmsMAX_PATH-1);
    }

    if (nParams > 2) FatalError("Too many CGATS files");
}