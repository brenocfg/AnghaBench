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
typedef  int /*<<< orphan*/  apdwStyles ;
typedef  int /*<<< orphan*/  albStyle ;
typedef  int /*<<< orphan*/  alHatch ;
typedef  int /*<<< orphan*/  aflJoin ;
typedef  int /*<<< orphan*/  aflEndCap ;
typedef  int /*<<< orphan*/  adwWidth ;
typedef  int /*<<< orphan*/  adwStyleCount ;
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UINT ;
typedef  int* PULONG ;
typedef  int DWORD ;

/* Variables and functions */
 int PS_ALTERNATE ; 
 int PS_COSMETIC ; 
 int PS_DASH ; 
 int PS_DASHDOT ; 
 int PS_DASHDOTDOT ; 
 int PS_DOT ; 
 int PS_ENDCAP_FLAT ; 
 int PS_ENDCAP_ROUND ; 
 int PS_ENDCAP_SQUARE ; 
 int PS_GEOMETRIC ; 
 int PS_INSIDEFRAME ; 
 int PS_JOIN_BEVEL ; 
 int PS_JOIN_MITER ; 
 int PS_JOIN_ROUND ; 
 int PS_NULL ; 
 int PS_SOLID ; 
 int PS_USERSTYLE ; 
 int /*<<< orphan*/  Test_ExtCreatePen_Helper (int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int*,int*) ; 

void Test_ExtCreatePen_Params2()
{
    ULONG aflPenType[] = {PS_COSMETIC, PS_GEOMETRIC, 0x20000};
    ULONG iType, iStyle, iEndCap, iJoin, iWidth, iStyleCount, iStyles, iBrushStyle, iHatch;
    DWORD adwStyles[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    DWORD adwStyles2[17] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

    printf("adwStyles=%p, adwStyles2=%p\n", adwStyles, adwStyles2);

    //for (iType = 0; iType < sizeof(aflPenType) / sizeof(aflPenType[0]); iType++)
    for (iType = 0; iType < 3; iType++)
    {
        ULONG aflPenStyle[] = {PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME, PS_USERSTYLE, PS_ALTERNATE, 9};
        //for (iStyle = 0; iStyle < sizeof(aflPenStyle) / sizeof(aflPenStyle[0]); iStyle++)
        for (iStyle = 0; iStyle < 10; iStyle++)
        {
            ULONG aflEndCap[] = {PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE, PS_ENDCAP_FLAT, 0x300, 0x400};
            for (iEndCap = 0; iEndCap < sizeof(aflEndCap) / sizeof(aflEndCap[0]); iEndCap++)
            {
                ULONG aflJoin[] = {PS_JOIN_ROUND, PS_JOIN_BEVEL, PS_JOIN_MITER, 0x3000, 0x4000};
                for (iJoin = 0; iJoin < sizeof(aflJoin) / sizeof(aflJoin[0]); iJoin++)
                {
                    DWORD adwWidth[] = {0, 1, 2};
                    ULONG flPenStyle = aflPenType[iType] | aflPenStyle[iStyle] | aflEndCap[iEndCap] | aflJoin[iJoin];

                    for (iWidth = 0; iWidth < sizeof(adwWidth) / sizeof(adwWidth[0]); iWidth++)
                    {
                        ULONG adwStyleCount[] = {0, 1, 2, 16, 17};
                        for (iStyleCount = 0; iStyleCount < sizeof(adwStyleCount) / sizeof(adwStyleCount[0]); iStyleCount++)
                        {
                            PULONG apdwStyles[] = {NULL, adwStyles, adwStyles2};
                            for (iStyles = 0; iStyles < sizeof(apdwStyles) / sizeof(apdwStyles[0]); iStyles++)
                            {
                                UINT albStyle[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                                for (iBrushStyle = 0; iBrushStyle < sizeof(albStyle) / sizeof(albStyle[0]); iBrushStyle++)
                                {
                                    ULONG_PTR alHatch[] = {0, 1, 6, 7, 8, 9, 10, 11, 12, 13};

                                    for (iHatch = 0; iHatch < sizeof(alHatch) / sizeof(alHatch[0]); iHatch++)
                                    {
                                        Test_ExtCreatePen_Helper(flPenStyle,
                                                                 adwWidth[iWidth],
                                                                 adwStyleCount[iStyleCount],
                                                                 apdwStyles[iStyles],
                                                                 albStyle[iBrushStyle],
                                                                 alHatch[iHatch]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}