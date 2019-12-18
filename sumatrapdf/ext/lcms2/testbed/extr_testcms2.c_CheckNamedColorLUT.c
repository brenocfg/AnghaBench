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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _cmsStageAllocNamedColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/ * cmsAllocNamedColorList (int /*<<< orphan*/ ,int,int,char*,char*) ; 
 int /*<<< orphan*/  cmsAppendNamedColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/  cmsFreeNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineEval16 (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckNamedColorLUT(void)
{
    cmsPipeline* lut = cmsPipelineAlloc(DbgThread(), 3, 3);
    cmsNAMEDCOLORLIST* nc;
    cmsInt32Number i,j, rc = 1, n2;
    cmsUInt16Number PCS[3];
    cmsUInt16Number Colorant[cmsMAXCHANNELS];
    char Name[255];
    cmsUInt16Number Inw[3], Outw[3];



    nc = cmsAllocNamedColorList(DbgThread(), 256, 3, "pre", "post");
    if (nc == NULL) return 0;

    for (i=0; i < 256; i++) {

        PCS[0] = PCS[1] = PCS[2] = (cmsUInt16Number) i;
        Colorant[0] = Colorant[1] = Colorant[2] = Colorant[3] = (cmsUInt16Number) i;

        sprintf(Name, "#%d", i);
        if (!cmsAppendNamedColor(DbgThread(), nc, Name, PCS, Colorant)) { rc = 0; break; }
    }

    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, _cmsStageAllocNamedColor(DbgThread(), nc, FALSE));

    cmsFreeNamedColorList(DbgThread(), nc);
    if (rc == 0) return 0;

    n2=0;

    for (j=0; j < 256; j++) {

        Inw[0] = (cmsUInt16Number) j;

        cmsPipelineEval16(DbgThread(), Inw, Outw, lut);
        for (i=0; i < 3; i++) {

            if (Outw[i] != j) {
                n2++;
            }
        }

    }

    cmsPipelineFree(DbgThread(), lut);
    return (n2 == 0);
}