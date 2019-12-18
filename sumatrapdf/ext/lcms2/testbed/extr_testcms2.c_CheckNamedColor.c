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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/ * cmsAllocNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  cmsAppendNamedColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckNamedColor(cmsInt32Number Pass,  cmsHPROFILE hProfile, cmsTagSignature tag, cmsInt32Number max_check, cmsBool  colorant_check)
{
    cmsNAMEDCOLORLIST* nc;
    cmsInt32Number i, j, rc;
    char Name[255];
    cmsUInt16Number PCS[3];
    cmsUInt16Number Colorant[cmsMAXCHANNELS];
    char CheckName[255];
    cmsUInt16Number CheckPCS[3];
    cmsUInt16Number CheckColorant[cmsMAXCHANNELS];

    switch (Pass) {

    case 1:

        nc = cmsAllocNamedColorList(DbgThread(), 0, 4, "prefix", "suffix");
        if (nc == NULL) return 0;

        for (i=0; i < max_check; i++) {

            PCS[0] = PCS[1] = PCS[2] = (cmsUInt16Number) i;
            Colorant[0] = Colorant[1] = Colorant[2] = Colorant[3] = (cmsUInt16Number) (max_check - i);

            sprintf(Name, "#%d", i);
            if (!cmsAppendNamedColor(DbgThread(), nc, Name, PCS, Colorant)) { Fail("Couldn't append named color"); return 0; }
        }

        rc = cmsWriteTag(DbgThread(), hProfile, tag, nc);
        cmsFreeNamedColorList(DbgThread(), nc);
        return rc;

    case 2:

        nc = (cmsNAMEDCOLORLIST *) cmsReadTag(DbgThread(), hProfile, tag);
        if (nc == NULL) return 0;

        for (i=0; i < max_check; i++) {

            CheckPCS[0] = CheckPCS[1] = CheckPCS[2] = (cmsUInt16Number) i;
            CheckColorant[0] = CheckColorant[1] = CheckColorant[2] = CheckColorant[3] = (cmsUInt16Number) (max_check - i);

            sprintf(CheckName, "#%d", i);
            if (!cmsNamedColorInfo(DbgThread(), nc, i, Name, NULL, NULL, PCS, Colorant)) { Fail("Invalid string"); return 0; }


            for (j=0; j < 3; j++) {
                if (CheckPCS[j] != PCS[j]) {  Fail("Invalid PCS"); return 0; }
            }

            // This is only used on named color list
            if (colorant_check) {

            for (j=0; j < 4; j++) {
                if (CheckColorant[j] != Colorant[j]) { Fail("Invalid Colorant"); return 0; };
            }
            }

            if (strcmp(Name, CheckName) != 0) { Fail("Invalid Name");  return 0; };
        }
        return 1;


    default: return 0;
    }
}