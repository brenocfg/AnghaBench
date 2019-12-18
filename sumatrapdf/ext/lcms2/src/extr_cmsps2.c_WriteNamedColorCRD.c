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
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  BuildColorantList (char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TYPE_NAMED_COLOR_INDEX ; 
 scalar_t__ T_CHANNELS (scalar_t__) ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ cmsFLAGS_NODEFAULTRESOURCEDEF ; 
 scalar_t__ cmsFormatterForColorspaceOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsGetNamedColorList (int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int cmsMAX_PATH ; 
 scalar_t__ cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int WriteNamedColorCRD(cmsContext ContextID, cmsIOHANDLER* m, cmsHPROFILE hNamedColor, cmsUInt32Number Intent, cmsUInt32Number dwFlags)
{
    cmsHTRANSFORM xform;
    cmsUInt32Number i, nColors, nColorant;
    cmsUInt32Number OutputFormat;
    char ColorName[cmsMAX_PATH];
    char Colorant[128];
    cmsNAMEDCOLORLIST* NamedColorList;


    OutputFormat = cmsFormatterForColorspaceOfProfile(ContextID, hNamedColor, 2, FALSE);
    nColorant    = T_CHANNELS(OutputFormat);


    xform = cmsCreateTransform(ContextID, hNamedColor, TYPE_NAMED_COLOR_INDEX, NULL, OutputFormat, Intent, dwFlags);
    if (xform == NULL) return 0;


    NamedColorList = cmsGetNamedColorList(xform);
    if (NamedColorList == NULL) return 0;

    _cmsIOPrintf(ContextID, m, "<<\n");
    _cmsIOPrintf(ContextID, m, "(colorlistcomment) (%s) \n", "Named profile");
    _cmsIOPrintf(ContextID, m, "(Prefix) [ (Pantone ) (PANTONE ) ]\n");
    _cmsIOPrintf(ContextID, m, "(Suffix) [ ( CV) ( CVC) ( C) ]\n");

    nColors   = cmsNamedColorCount(ContextID, NamedColorList);

    for (i=0; i < nColors; i++) {

        cmsUInt16Number In[1];
        cmsUInt16Number Out[cmsMAXCHANNELS];

        In[0] = (cmsUInt16Number) i;

        if (!cmsNamedColorInfo(ContextID, NamedColorList, i, ColorName, NULL, NULL, NULL, NULL))
                continue;

        cmsDoTransform(ContextID, xform, In, Out, 1);
        BuildColorantList(Colorant, nColorant, Out);
        _cmsIOPrintf(ContextID, m, "  (%s) [ %s ]\n", ColorName, Colorant);
    }

    _cmsIOPrintf(ContextID, m, "   >>");

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

    _cmsIOPrintf(ContextID, m, " /Current exch /HPSpotTable defineresource pop\n");
    }

    cmsDeleteTransform(ContextID, xform);
    return 1;
}