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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveCR (char*) ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigCopyrightTag ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void EmitHeader(cmsContext ContextID, cmsIOHANDLER* m, const char* Title, cmsHPROFILE hProfile)
{
    time_t timer;
    cmsMLU *Description, *Copyright;
    char DescASCII[256], CopyrightASCII[256];

    time(&timer);

    Description = (cmsMLU*) cmsReadTag(ContextID, hProfile, cmsSigProfileDescriptionTag);
    Copyright   = (cmsMLU*) cmsReadTag(ContextID, hProfile, cmsSigCopyrightTag);

    DescASCII[0] = DescASCII[255] = 0;
    CopyrightASCII[0] = CopyrightASCII[255] = 0;

    if (Description != NULL) cmsMLUgetASCII(ContextID, Description,  cmsNoLanguage, cmsNoCountry, DescASCII,       255);
    if (Copyright != NULL)   cmsMLUgetASCII(ContextID, Copyright,    cmsNoLanguage, cmsNoCountry, CopyrightASCII,  255);

    _cmsIOPrintf(ContextID, m, "%%!PS-Adobe-3.0\n");
    _cmsIOPrintf(ContextID, m, "%%\n");
    _cmsIOPrintf(ContextID, m, "%% %s\n", Title);
    _cmsIOPrintf(ContextID, m, "%% Source: %s\n", RemoveCR(DescASCII));
    _cmsIOPrintf(ContextID, m, "%%         %s\n", RemoveCR(CopyrightASCII));
    _cmsIOPrintf(ContextID, m, "%% Created: %s", ctime(&timer)); // ctime appends a \n!!!
    _cmsIOPrintf(ContextID, m, "%%\n");
    _cmsIOPrintf(ContextID, m, "%%%%BeginResource\n");

}