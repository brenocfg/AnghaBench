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
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  SetRange (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsAllocNamedColorList (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsAppendNamedColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMAXCHANNELS ; 
 int cmsMAX_PATH ; 
#define  cmsSigCmyData 138 
#define  cmsSigCmykData 137 
#define  cmsSigGrayData 136 
#define  cmsSigHlsData 135 
#define  cmsSigHsvData 134 
#define  cmsSigLabData 133 
#define  cmsSigLuvData 132 
#define  cmsSigRgbData 131 
#define  cmsSigXYZData 130 
#define  cmsSigYCbCrData 129 
#define  cmsSigYxyData 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static
cmsNAMEDCOLORLIST* ComponentNames(cmsContext ContextID, cmsColorSpaceSignature space, cmsBool IsInput)
{
    cmsNAMEDCOLORLIST* out;
    int i, n;
    char Buffer[cmsMAX_PATH];

    out = cmsAllocNamedColorList(0, 12, cmsMAXCHANNELS, "", "");
    if (out == NULL) return NULL;

    switch (space) {

    case cmsSigXYZData:
        SetRange(100, IsInput);
        cmsAppendNamedColor(ContextID, out, "X", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "Y", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "Z", NULL, NULL);
        break;

    case cmsSigLabData:
        SetRange(1, IsInput);
        cmsAppendNamedColor(ContextID, out, "L*", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "a*", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "b*", NULL, NULL);
        break;

    case cmsSigLuvData:
        SetRange(1, IsInput);
        cmsAppendNamedColor(ContextID, out, "L", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "u", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "v", NULL, NULL);
        break;

    case cmsSigYCbCrData:
        SetRange(255, IsInput);
        cmsAppendNamedColor(ContextID, out, "Y", NULL, NULL );
        cmsAppendNamedColor(ContextID, out, "Cb", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "Cr", NULL, NULL);
        break;


    case cmsSigYxyData:
        SetRange(1, IsInput);
        cmsAppendNamedColor(ContextID, out, "Y", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "x", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "y", NULL, NULL);
        break;

    case cmsSigRgbData:
        SetRange(255, IsInput);
        cmsAppendNamedColor(ContextID, out, "R", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "G", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "B", NULL, NULL);
        break;

    case cmsSigGrayData:
        SetRange(255, IsInput);
        cmsAppendNamedColor(ContextID, out, "G", NULL, NULL);
        break;

    case cmsSigHsvData:
        SetRange(255, IsInput);
        cmsAppendNamedColor(ContextID, out, "H", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "s", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "v", NULL, NULL);
        break;

    case cmsSigHlsData:
        SetRange(255, IsInput);
        cmsAppendNamedColor(ContextID, out, "H", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "l", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "s", NULL, NULL);
        break;

    case cmsSigCmykData:
        SetRange(1, IsInput);
        cmsAppendNamedColor(ContextID, out, "C", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "M", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "Y", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "K", NULL, NULL);
        break;

    case cmsSigCmyData:
        SetRange(1, IsInput);
        cmsAppendNamedColor(ContextID, out, "C", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "M", NULL, NULL);
        cmsAppendNamedColor(ContextID, out, "Y", NULL, NULL);
        break;

    default:

        SetRange(1, IsInput);

        n = cmsChannelsOf(ContextID, space);

        for (i=0; i < n; i++) {

            sprintf(Buffer, "Channel #%d", i + 1);
            cmsAppendNamedColor(ContextID, out, Buffer, NULL, NULL);
        }
    }

    return out;

}