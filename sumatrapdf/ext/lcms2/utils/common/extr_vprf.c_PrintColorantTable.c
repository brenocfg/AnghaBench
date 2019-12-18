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
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ cmsIsTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsMAX_PATH ; 
 int cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static
void PrintColorantTable(cmsContext ContextID, cmsHPROFILE hInput, cmsTagSignature Sig, const char* Title)
{
    cmsNAMEDCOLORLIST* list;
    int i, n;

    if (cmsIsTag(ContextID, hInput, Sig)) {

        printf("%s:\n", Title);

        list = (cmsNAMEDCOLORLIST*) cmsReadTag(ContextID, hInput, Sig);
        if (list == NULL) {
            printf("(Unavailable)\n");
            return;
        }

        n = cmsNamedColorCount(ContextID, list);
        for (i=0; i < n; i++) {

            char Name[cmsMAX_PATH];

            cmsNamedColorInfo(ContextID, list, i, Name, NULL, NULL, NULL, NULL);
            printf("\t%s\n", Name);
        }

        printf("\n");
    }

}