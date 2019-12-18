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
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  cmsSigCopyrightTag ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool SetTextTags(cmsHPROFILE hProfile)
{
    cmsMLU *DescriptionMLU, *CopyrightMLU;
    cmsBool  rc = FALSE;
  
    DescriptionMLU  = cmsMLUalloc(0, 1);
    CopyrightMLU    = cmsMLUalloc(0, 1);

    if (DescriptionMLU == NULL || CopyrightMLU == NULL) goto Error;

    if (!cmsMLUsetASCII(DescriptionMLU,  "en", "US", "Little cms Tiff8 CIELab")) goto Error;
    if (!cmsMLUsetASCII(CopyrightMLU,    "en", "US", "Copyright (c) Marti Maria, 2010. All rights reserved.")) goto Error;

    if (!cmsWriteTag(hProfile, cmsSigProfileDescriptionTag,  DescriptionMLU)) goto Error;
    if (!cmsWriteTag(hProfile, cmsSigCopyrightTag,           CopyrightMLU)) goto Error;     

    rc = TRUE;

Error:

    if (DescriptionMLU)
        cmsMLUfree(DescriptionMLU);
    if (CopyrightMLU)
        cmsMLUfree(CopyrightMLU);
    return rc;
}