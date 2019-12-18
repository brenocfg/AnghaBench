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
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/ * cmsAllocNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  cmsAppendNamedColor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFreeNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int cmsMAX_PATH ; 
 int cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsNamedColorIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigNamedColor2Tag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckNamedColorList(void)
{
    cmsNAMEDCOLORLIST* nc = NULL, *nc2;
    cmsInt32Number i, j, rc=1;
    char Name[cmsMAX_PATH];
    cmsUInt16Number PCS[3];
    cmsUInt16Number Colorant[cmsMAXCHANNELS];
    char CheckName[cmsMAX_PATH];
    cmsUInt16Number CheckPCS[3];
    cmsUInt16Number CheckColorant[cmsMAXCHANNELS];
    cmsHPROFILE h;

    nc = cmsAllocNamedColorList(DbgThread(), 0, 4, "prefix", "suffix");
    if (nc == NULL) return 0;

    for (i=0; i < 4096; i++) {


        PCS[0] = PCS[1] = PCS[2] = (cmsUInt16Number) i;
        Colorant[0] = Colorant[1] = Colorant[2] = Colorant[3] = (cmsUInt16Number) (4096 - i);

        sprintf(Name, "#%d", i);
        if (!cmsAppendNamedColor(DbgThread(), nc, Name, PCS, Colorant)) { rc = 0; break; }
    }

    for (i=0; i < 4096; i++) {

        CheckPCS[0] = CheckPCS[1] = CheckPCS[2] = (cmsUInt16Number) i;
        CheckColorant[0] = CheckColorant[1] = CheckColorant[2] = CheckColorant[3] = (cmsUInt16Number) (4096 - i);

        sprintf(CheckName, "#%d", i);
        if (!cmsNamedColorInfo(DbgThread(), nc, i, Name, NULL, NULL, PCS, Colorant)) { rc = 0; goto Error; }


        for (j=0; j < 3; j++) {
            if (CheckPCS[j] != PCS[j]) { rc = 0; Fail("Invalid PCS"); goto Error; }
        }

        for (j=0; j < 4; j++) {
            if (CheckColorant[j] != Colorant[j]) { rc = 0; Fail("Invalid Colorant"); goto Error; };
        }

        if (strcmp(Name, CheckName) != 0) {rc = 0; Fail("Invalid Name"); goto Error; };
    }

    h = cmsOpenProfileFromFile(DbgThread(), "namedcol.icc", "w");
    if (h == NULL) return 0;
    if (!cmsWriteTag(DbgThread(), h, cmsSigNamedColor2Tag, nc)) return 0;
    cmsCloseProfile(DbgThread(), h);
    cmsFreeNamedColorList(DbgThread(), nc);
    nc = NULL;

    h = cmsOpenProfileFromFile(DbgThread(), "namedcol.icc", "r");
    nc2 = (cmsNAMEDCOLORLIST *) cmsReadTag(DbgThread(), h, cmsSigNamedColor2Tag);

    if (cmsNamedColorCount(DbgThread(), nc2) != 4096) { rc = 0; Fail("Invalid count"); goto Error; }

    i = cmsNamedColorIndex(DbgThread(), nc2, "#123");
    if (i != 123) { rc = 0; Fail("Invalid index"); goto Error; }


    for (i=0; i < 4096; i++) {

        CheckPCS[0] = CheckPCS[1] = CheckPCS[2] = (cmsUInt16Number) i;
        CheckColorant[0] = CheckColorant[1] = CheckColorant[2] = CheckColorant[3] = (cmsUInt16Number) (4096 - i);

        sprintf(CheckName, "#%d", i);
        if (!cmsNamedColorInfo(DbgThread(), nc2, i, Name, NULL, NULL, PCS, Colorant)) { rc = 0; goto Error; }


        for (j=0; j < 3; j++) {
            if (CheckPCS[j] != PCS[j]) { rc = 0; Fail("Invalid PCS"); goto Error; }
        }

        for (j=0; j < 4; j++) {
            if (CheckColorant[j] != Colorant[j]) { rc = 0; Fail("Invalid Colorant"); goto Error; };
        }

        if (strcmp(Name, CheckName) != 0) {rc = 0; Fail("Invalid Name"); goto Error; };
    }

    cmsCloseProfile(DbgThread(), h);
    remove("namedcol.icc");

Error:
    if (nc != NULL) cmsFreeNamedColorList(DbgThread(), nc);
    return rc;
}