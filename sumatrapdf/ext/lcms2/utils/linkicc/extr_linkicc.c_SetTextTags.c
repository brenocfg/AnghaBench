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
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  Copyright ; 
 int /*<<< orphan*/  Description ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigCopyrightTag ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool SetTextTags(cmsContext ContextID, cmsHPROFILE hProfile)
{
    cmsMLU *DescriptionMLU, *CopyrightMLU;
    cmsBool  rc = FALSE;

    DescriptionMLU  = cmsMLUalloc(ContextID, 1);
    CopyrightMLU    = cmsMLUalloc(ContextID, 1);

    if (DescriptionMLU == NULL || CopyrightMLU == NULL) goto Error;

    if (!cmsMLUsetASCII(ContextID, DescriptionMLU,  "en", "US", Description)) goto Error;
    if (!cmsMLUsetASCII(ContextID, CopyrightMLU,    "en", "US", Copyright)) goto Error;

    if (!cmsWriteTag(ContextID, hProfile, cmsSigProfileDescriptionTag,  DescriptionMLU)) goto Error;
    if (!cmsWriteTag(ContextID, hProfile, cmsSigCopyrightTag,           CopyrightMLU)) goto Error;

    rc = TRUE;

Error:

    if (DescriptionMLU)
        cmsMLUfree(ContextID, DescriptionMLU);
    if (CopyrightMLU)
        cmsMLUfree(ContextID, CopyrightMLU);
    return rc;
}