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
 char* IncludePart ; 
 int OutputColorSpace ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsIT8DefineDblFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsIT8SetComment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsIT8SetDataFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  cmsIT8SetPropertyDbl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsIT8SetPropertyStr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
#define  cmsSig10colorData 148 
#define  cmsSig11colorData 147 
#define  cmsSig12colorData 146 
#define  cmsSig13colorData 145 
#define  cmsSig14colorData 144 
#define  cmsSig15colorData 143 
#define  cmsSig1colorData 142 
#define  cmsSig2colorData 141 
#define  cmsSig3colorData 140 
#define  cmsSig4colorData 139 
#define  cmsSig5colorData 138 
#define  cmsSig6colorData 137 
#define  cmsSig7colorData 136 
#define  cmsSig8colorData 135 
#define  cmsSig9colorData 134 
#define  cmsSigCmyData 133 
#define  cmsSigCmykData 132 
#define  cmsSigGrayData 131 
#define  cmsSigLabData 130 
#define  cmsSigRgbData 129 
#define  cmsSigXYZData 128 
 int /*<<< orphan*/  hIT8out ; 
 int nMaxPatches ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static
void SetOutputDataFormat(cmsContext ContextID)
{
    cmsIT8DefineDblFormat(ContextID, hIT8out, "%.4g");
    cmsIT8SetPropertyStr(ContextID, hIT8out, "ORIGINATOR", "icctrans");

    if (IncludePart != NULL)
        cmsIT8SetPropertyStr(ContextID, hIT8out, ".INCLUDE", IncludePart);

    cmsIT8SetComment(ContextID, hIT8out, "Data follows");
    cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_SETS", nMaxPatches);


    switch (OutputColorSpace) {


        // Encoding should follow CGATS specification.

    case cmsSigXYZData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "XYZ_X");
        cmsIT8SetDataFormat(ContextID, hIT8out, 2, "XYZ_Y");
        cmsIT8SetDataFormat(ContextID, hIT8out, 3, "XYZ_Z");
        break;

    case cmsSigLabData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "LAB_L");
        cmsIT8SetDataFormat(ContextID, hIT8out, 2, "LAB_A");
        cmsIT8SetDataFormat(ContextID, hIT8out, 3, "LAB_B");
        break;


    case cmsSigRgbData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "RGB_R");
        cmsIT8SetDataFormat(ContextID, hIT8out, 2, "RGB_G");
        cmsIT8SetDataFormat(ContextID, hIT8out, 3, "RGB_B");
        break;

    case cmsSigGrayData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 2);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "GRAY");
        break;

    case cmsSigCmykData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 5);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "CMYK_C");
        cmsIT8SetDataFormat(ContextID, hIT8out, 2, "CMYK_M");
        cmsIT8SetDataFormat(ContextID, hIT8out, 3, "CMYK_Y");
        cmsIT8SetDataFormat(ContextID, hIT8out, 4, "CMYK_K");
        break;

    case cmsSigCmyData:
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", 4);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");
        cmsIT8SetDataFormat(ContextID, hIT8out, 1, "CMY_C");
        cmsIT8SetDataFormat(ContextID, hIT8out, 2, "CMY_M");
        cmsIT8SetDataFormat(ContextID, hIT8out, 3, "CMY_Y");
        break;

    case cmsSig1colorData:
    case cmsSig2colorData:
    case cmsSig3colorData:
    case cmsSig4colorData:
    case cmsSig5colorData:
    case cmsSig6colorData:
    case cmsSig7colorData:
    case cmsSig8colorData:
    case cmsSig9colorData:
    case cmsSig10colorData:
    case cmsSig11colorData:
    case cmsSig12colorData:
    case cmsSig13colorData:
    case cmsSig14colorData:
    case cmsSig15colorData:
        {
            int i, n;
            char Buffer[255];

            n = cmsChannelsOf(ContextID, OutputColorSpace);
            cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", n+1);
            cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");

            for (i=1; i <= n; i++) {
                sprintf(Buffer, "%dCLR_%d", n, i);
                cmsIT8SetDataFormat(ContextID, hIT8out, i, Buffer);
            }
        }
        break;

    default: {

        int i, n;
        char Buffer[255];

        n = cmsChannelsOf(ContextID, OutputColorSpace);
        cmsIT8SetPropertyDbl(ContextID, hIT8out, "NUMBER_OF_FIELDS", n+1);
        cmsIT8SetDataFormat(ContextID, hIT8out, 0, "SAMPLE_ID");

        for (i=1; i <= n; i++) {
            sprintf(Buffer, "CHAN_%d", i);
            cmsIT8SetDataFormat(ContextID, hIT8out, i, Buffer);
        }
    }
    }
}