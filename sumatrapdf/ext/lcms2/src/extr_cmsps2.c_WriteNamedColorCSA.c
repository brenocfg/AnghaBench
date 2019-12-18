#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int /*<<< orphan*/  TYPE_NAMED_COLOR_INDEX ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * cmsGetNamedColorList (int /*<<< orphan*/ *) ; 
 int cmsMAX_PATH ; 
 scalar_t__ cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int WriteNamedColorCSA(cmsContext ContextID, cmsIOHANDLER* m, cmsHPROFILE hNamedColor, cmsUInt32Number Intent)
{
    cmsHTRANSFORM xform;
    cmsHPROFILE   hLab;
    cmsUInt32Number i, nColors;
    char ColorName[cmsMAX_PATH];
    cmsNAMEDCOLORLIST* NamedColorList;

    hLab  = cmsCreateLab4Profile(ContextID, NULL);
    xform = cmsCreateTransform(ContextID, hNamedColor, TYPE_NAMED_COLOR_INDEX, hLab, TYPE_Lab_DBL, Intent, 0);
    if (xform == NULL) return 0;

    NamedColorList = cmsGetNamedColorList(xform);
    if (NamedColorList == NULL) return 0;

    _cmsIOPrintf(ContextID, m, "<<\n");
    _cmsIOPrintf(ContextID, m, "(colorlistcomment) (%s)\n", "Named color CSA");
    _cmsIOPrintf(ContextID, m, "(Prefix) [ (Pantone ) (PANTONE ) ]\n");
    _cmsIOPrintf(ContextID, m, "(Suffix) [ ( CV) ( CVC) ( C) ]\n");

    nColors   = cmsNamedColorCount(ContextID, NamedColorList);


    for (i=0; i < nColors; i++) {

        cmsUInt16Number In[1];
        cmsCIELab Lab;

        In[0] = (cmsUInt16Number) i;

        if (!cmsNamedColorInfo(ContextID, NamedColorList, i, ColorName, NULL, NULL, NULL, NULL))
                continue;

        cmsDoTransform(ContextID, xform, In, &Lab, 1);
        _cmsIOPrintf(ContextID, m, "  (%s) [ %.3f %.3f %.3f ]\n", ColorName, Lab.L, Lab.a, Lab.b);
    }



    _cmsIOPrintf(ContextID, m, ">>\n");

    cmsDeleteTransform(ContextID, xform);
    cmsCloseProfile(ContextID, hLab);
    return 1;
}