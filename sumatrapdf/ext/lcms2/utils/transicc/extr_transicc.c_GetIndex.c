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
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  FatalError (char*,int) ; 
 int /*<<< orphan*/  GetLine (int /*<<< orphan*/ ,char*,char*,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/ * cmsGetNamedColorList (int /*<<< orphan*/ ) ; 
 int cmsMAX_PATH ; 
 int cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hTrans ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

__attribute__((used)) static
cmsUInt16Number GetIndex(cmsContext ContextID)
{
    char Buffer[4096], Name[cmsMAX_PATH], Prefix[40], Suffix[40];
    int index, max;
    const cmsNAMEDCOLORLIST* NamedColorList;

    NamedColorList = cmsGetNamedColorList(hTrans);
    if (NamedColorList == NULL) return 0;

    max = cmsNamedColorCount(ContextID, NamedColorList)-1;

    GetLine(ContextID, Buffer, "Color index (0..%d)? ", max);
    index = atoi(Buffer);

    if (index > max)
        FatalError("Named color %d out of range!", index);

    cmsNamedColorInfo(ContextID, NamedColorList, index, Name, Prefix, Suffix, NULL, NULL);

    printf("\n%s %s %s\n", Prefix, Name, Suffix);

    return (cmsUInt16Number) index;
}